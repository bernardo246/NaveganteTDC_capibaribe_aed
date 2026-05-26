#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// bibliotecas pra instalar
#include <curl/curl.h>
#include <cjson/cJSON.h>

#include "../include/clima.h"


char *API_URL = "https://api.open-meteo.com/v1/forecast?latitude=-8.063169&longitude=-34.871139&current=rain,is_day&models=best_match";    


typedef struct ApeiResponse {
    char* text;
    size_t size;
} ApiResponse;

size_t callback(void *conteudo, size_t size, size_t nmemb, void *userdata){
    size_t total_size = size * nmemb;
    ApiResponse* response = (ApiResponse*) userdata;

    char* temp = realloc(response->text, response->size + total_size + 1);
    if (temp == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 0; // falha na alocação
    }
    response->text = temp;

    memcpy(response->text + response->size, conteudo, total_size);
    response->size += total_size;
    response->text[response->size] = '\0'; // null-terminator

    return total_size;
}


// funcao para fazer a requisicao da api pra fazer os dados do clima e processar a resposta
char* request_wheatherAPI(char *content) {
    
    ApiResponse response = {0};

    CURL *curl = curl_easy_init();

    if (curl){

        curl_easy_setopt(curl, CURLOPT_URL, API_URL); // aqui eu seto a url da api.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback); // aqui eu seto a funcao de callback para processar a resposta da api.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); // aqui eu seto o ponteiro para a struct ApiResponse, onde a resposta da api sera armazenada.


        CURLcode result = curl_easy_perform(curl); // aqui eu executo a requisição.
        if (result != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
            curl_easy_cleanup(curl);
            free(response.text); // libera o que foi alocado
            return NULL;         // sinaliza erro pra quem chamou
        }

        curl_easy_cleanup(curl);
        return response.text;
    }
    else{
        fprintf(stderr, "Erro ao inicializar CURL\n");
        return NULL;
    }
}

void print_request(){
    char *response = request_wheatherAPI(API_URL);
    if (response) {
        printf("Resposta da API: %s\n", response);
        free(response); // libera a memória alocada para a resposta
    } else {
        fprintf(stderr, "Falha ao obter resposta da API\n");
    }
}

void atualizar_clima(Clima* clima) {
    static double ultimo_update = -900.0; // força update na primeira chamada

    double agora = GetTime();
    if (agora - ultimo_update < 900.0) return; // ainda não passou 15 minutos

    ultimo_update = agora;

    char *response = request_wheatherAPI(API_URL);
    if (response) {
        cJSON *json = cJSON_Parse(response);
        if (json) {
            cJSON *current = cJSON_GetObjectItem(json, "current");
            if (current) {
                clima->noite = !cJSON_GetObjectItem(current, "is_day")->valueint;
                float rain = cJSON_GetObjectItem(current, "rain")->valuedouble;

                if (rain > 0) {
                    clima->tipo = CLIMA_CHUVA;
                    clima->intensidade = rain;
                } else {
                    clima->tipo = CLIMA_SOL;
                    clima->intensidade = 0;
                }
            }
            cJSON_Delete(json);
        } else {
            fprintf(stderr, "Erro ao parsear JSON: %s\n", cJSON_GetErrorPtr());
        }
        free(response);
    } else {
        fprintf(stderr, "Falha ao obter resposta da API\n");
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void sha512_file(const char *filename, char *outputBuffer) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("无法打开文件\n");
        return;
    }

    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha512();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);

    unsigned char buffer[1024];
    size_t bytesRead = 0;
    
    while ((bytesRead = fread(buffer, 1, 1024, file)) != 0) {
        EVP_DigestUpdate(mdctx, buffer, bytesRead);
    }

    EVP_DigestFinal_ex(mdctx, hash, &hashLen);

    EVP_MD_CTX_free(mdctx);
    fclose(file);

    for (int i = 0; i < hashLen; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    outputBuffer[hashLen * 2] = 0;
}

void sha512_string(const char *str, char *outputBuffer) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_sha512();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    
    EVP_DigestUpdate(mdctx, str, strlen(str));
    
    EVP_DigestFinal_ex(mdctx, hash, &hashLen);

    EVP_MD_CTX_free(mdctx);

    for (int i = 0; i < hashLen; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[hashLen * 2] = 0;
}

int main() {
    char *filename = "/home/lja/user/preview_learning/10_project_network/7_-group_-cloud_-storage/client/tests/lja/tcp_ip.pdf";
    char hash_output[1024] = {0};

    sha512_file(filename, hash_output);
    printf("File: %s\n", filename);
    printf("SHA-512 Hash: %s\n", hash_output);
    printf("len = %ld\n", strlen(hash_output));

    printf("start re sha512 hash\n");
    
    char re_hash[1024] = {0};
    sha512_string(filename, re_hash);
    printf("re_hash = %s\n", re_hash);

    return 0;
}
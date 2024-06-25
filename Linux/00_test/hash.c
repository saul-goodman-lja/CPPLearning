#include <my_header.h>
#include <openssl/sha.h>
#define BUFFER_SIZE 1024

static void analyze_hash(char *buf, char *file_path, const char *sha_path){
    // 读取文件，解析哈希值
    FILE *pipe = popen(sha_path, "r");
    fread(buf,1, sizeof(buf), pipe);
    int len = strlen(buf);
    char name[1024] = {0};
    name[0] = ' ';
    name[1] = ' ';
    memcpy(name + 2, file_path, strlen(file_path));
    memset(buf + strlen(buf) - strlen(name) - 1, 0, strlen(name));
    pclose(pipe);
}




void sha512_file(const char *filename, char outputBuffer[129]) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("无法打开文件\n");
        return;
    }

    SHA512_CTX sha512;
    SHA512_Init(&sha512);

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead = 0;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) != 0) {
        SHA512_Update(&sha512, buffer, bytesRead);
    }

    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_Final(hash, &sha512);

    fclose(file);

    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    
    outputBuffer[128] = 0;
}


int main(void){

    // char *sha_path = "echo 123 | shasum";

    // char buf[1024] = {0};
    // char file_path[1024] = {0};
    // file_path[0] = '-';

    // FILE *pipe = popen(sha_path, "r");
    // fread(buf,1, sizeof(buf), pipe);
    // printf("len = %ld\n", strlen(buf));
    // // memset(buf + strlen(buf) - 5, 0, 3);
    // pclose(pipe);

    // printf("hash = %s\n", buf);

    // return 0;


    char *filename = "hash.c";
    char hash_output[129];

    sha512_file(filename, hash_output);

    printf("File: %s\n", filename);
    printf("SHA-512 Hash: %s\n", hash_output);

    return 0;
}
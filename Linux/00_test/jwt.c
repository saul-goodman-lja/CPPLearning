// 加密
#include <my_header.h>
#include <l8w8jwt/encode.h>
#include <l8w8jwt/decode.h>


/**
* 函数名: jwt_encrypt
* 描述: token 加密
* 参数: 
* - char *token: 返回加密后的token
* - const char *username: 要加密的用户名
* - const char *user_id: 用户id
* 返回值: NULL
*/
void jwt_encrypt(char *token, const char *user_name, const char *user_id){
    memset(token, 0, 1024);
    // 用于存储生成的JWT字符串
    char* jwt; 

    // JWT字符串的长度
    size_t jwt_length;  

    // 初始化编码参数结构体
    struct l8w8jwt_encoding_params params;
    l8w8jwt_encoding_params_init(&params); 

    // 设置JWT使用的算法，这里使用HS512
    params.alg = L8W8JWT_ALG_HS512;  

    // 设置JWT的主要荷载部分内容:
    // user_id
    char uid[24] = {0};
    memcpy(uid, user_id, strlen(user_id));
    params.sub = uid;  
    // TODO
    // 签发者 : user_name user_id
    char username[1024] = {0};
    memcpy(username, user_name, strlen(user_name));
    params.iss = username;

    // 接收方
    params.aud = "server";  
    // token过期/有效时间(0x7fffffff:最大值-> 2038年1月19日)
    params.exp = 0x7fffffff;  
    // token签发时间
    params.iat = 0;  

    // 设置加密密钥
    params.secret_key = (unsigned char*)"Personal cloud project of c plus plus 57 phase 7 group";
    params.secret_key_length = strlen((char *)params.secret_key);

    // 输出变量
    params.out = &jwt;
    params.out_length = &jwt_length;

    // 加密
    l8w8jwt_encode(&params);

    memcpy(token, jwt, strlen(jwt));

    // 释放token 字符串的内存
    l8w8jwt_free(jwt);
}


/**
* 函数名: jwt_decrypt
* 描述: token 解密
* 参数: 
* - const char *token: 要解密的token
* - char *username: 返回解密后的用户名
* - char *user_id: 用户id
* 返回值: NULL
*/
void jwt_decrypt(const char *token, char *user_name, char *user_id){
    memset(user_name, 0, 1024);
    // 初始化解码参数结构体
    struct l8w8jwt_decoding_params params;
    l8w8jwt_decoding_params_init(&params);  

    // 设置JWT使用的算法，这里使用HS512
    params.alg = L8W8JWT_ALG_HS512;  

    // 填入token字符串和长度
    params.jwt = (char*)token;
    params.jwt_length = strlen(token);

    // 设置密钥
    char *key="Personal cloud project of c plus plus 57 phase 7 group";
    params.verification_key = (unsigned char*)key;
    params.verification_key_length = strlen(key);

    // 定义: 接收结果的指针和变量
    struct l8w8jwt_claim *claims = NULL;
    size_t claim_count = 0;
    enum l8w8jwt_validation_result validation_result;

    // 解码: 获得token中存储的信息
    int decode_result = l8w8jwt_decode(&params, &validation_result, &claims, &claim_count);

    // 判断是否是正确的token
    if (decode_result == L8W8JWT_SUCCESS && validation_result == L8W8JWT_VALID) {
        // printf("Token validation successful!\n");

        // 打印token中解码出来的荷载信息
        // for (size_t i = 0; i < claim_count; i++) {
        //     printf("Claim [%zu]: %s = %s\n", i, claims[i].key, claims[i].value);
        // }
        
    } else {
        printf("Token validation failed!\n");
    }
    memcpy(user_id, claims[3].value, strlen(claims[3].value));
    memcpy(user_name, claims[4].value, strlen(claims[4].value));

    l8w8jwt_free_claims(claims, claim_count);
} 

int main(void)
{
    char token[1024] = {0};
    char *username = "lja";
    char *uid = "123456";
    jwt_encrypt(token, username,uid);
    // printf("token = %s \n", token);

    char u_name[1024] = {0};
    char u_id[24] = {0};
    jwt_decrypt(token, u_name, u_id);

    printf("username = |%s|\n user_id = |%s|", u_name, u_id);

    return 0;
}   
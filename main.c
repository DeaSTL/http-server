#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>





typedef enum content_type_s{
  TEXT_HTML,
  TEXT_CSS,
  TEXT_JS,
  IMAGE_PNG,
  IMAGE_JPEG,
  IMAGE_GIF,
  IMAGE_SVG,
  IMAGE_ICO,
  APPLICATION_JSON,
  APPLICATION_XML,
  APPLICATION_PDF,
  APPLICATION_ZIP,
  APPLICATION_OCTET_STREAM
} content_type_t;

typedef enum request_method_s{
  GET,
  POST,
  PUT,
  DELETE,
  HEAD,
  OPTIONS,
  CONNECT,
  TRACE,
  PATCH
} request_method_t;

request_method_t parse_method(char* method){
  if(strcmp(method, "GET") == 0){
    return GET;
  }else if(strcmp(method, "POST") == 0){
    return POST;
  }else if(strcmp(method, "PUT") == 0){
    return PUT;
  }else if(strcmp(method, "DELETE") == 0){
    return DELETE;
  }else if(strcmp(method, "HEAD") == 0){
    return HEAD;
  }else if(strcmp(method, "OPTIONS") == 0){
    return OPTIONS;
  }else if(strcmp(method, "CONNECT") == 0){
    return CONNECT;
  }else if(strcmp(method, "TRACE") == 0){
    return TRACE;
  }else if(strcmp(method, "PATCH") == 0){
    return PATCH;
  }
  return -1;
}
const char* get_content_type_str(content_type_t content_type){
  switch(content_type){
    case(TEXT_HTML):
      return "text/html";
    case(TEXT_CSS):
      return "text/css";
    case(TEXT_JS):
      return "text/javascript";
    case(IMAGE_PNG):
      return "image/png";
    case(IMAGE_JPEG):
      return "image/jpeg";
    case(IMAGE_GIF):
      return "image/gif";
    case(IMAGE_SVG):
      return "image/svg+xml";
    case(IMAGE_ICO):
      return "image/x-icon";
    case(APPLICATION_JSON):
      return "application/json";
    case(APPLICATION_XML):
      return "application/xml";
    case(APPLICATION_PDF):
      return "application/pdf";
    case(APPLICATION_ZIP):
      return "application/zip";
    case(APPLICATION_OCTET_STREAM):
      return "application/octet-stream";
  }
  return "text/html";
}
const char* get_status_code_message(int status_code){
  switch(status_code){
    case(200):
      return "OK";
    case(201):
      return "Created";
    case(202):
      return "Accepted";
    case(203):
      return "Non-Authoritative Information";
    case(204):
      return "No Content";
    case(205):
      return "Reset Content";
    case(206):
      return "Partial Content";
    case(300):
      return "Multiple Choices";
    case(301):
      return "Moved Permanently";
    case(302):
      return "Found";
    case(303):
      return "See Other";
    case(304):
      return "Not Modified";
    case(305):
      return "Use Proxy";
    case(307):
      return "Temporary Redirect";
    case(400):
      return "Bad Request";
    case(401):
      return "Unauthorized";
    case(402):
      return "Payment Required";
    case(403):
      return "Forbidden";
    case(404):
      return "Not Found";
    case(405):
      return "Method Not Allowed";
    case(406):
      return "Not Acceptable";
    case(407):
      return "Proxy Authentication Required";
    case(408):
      return "Request Timeout";
    case(409):
      return "Conflict";
    case(410):
      return "Gone";
    case(411):
      return "Length Required";
    case(412):
      return "Precondition Failed";
    case(413):
      return "Request Entity Too Large";
    case(414):
      return "Request-URI Too Long";
    case(415):
      return "Unsupported Media Type";
    case(416):
      return "Requested Range Not Satisfiable";
    case(417):
      return "Expectation Failed";
    case(500):
      return "Internal Server Error";
    default:
      return "Internal Server Error";
  }
}

content_type_t parse_content_type(char* content_type){
  if(strcmp(content_type, "text/html") == 0){
    return TEXT_HTML;
  }else if(strcmp(content_type, "text/css") == 0){
    return TEXT_CSS;
  }else if(strcmp(content_type, "text/javascript") == 0){
    return TEXT_JS;
  }else if(strcmp(content_type, "image/png") == 0){
    return IMAGE_PNG;
  }else if(strcmp(content_type, "image/jpeg") == 0){
    return IMAGE_JPEG;
  }else if(strcmp(content_type, "image/gif") == 0){
    return IMAGE_GIF;
  }else if(strcmp(content_type, "image/svg+xml") == 0){
    return IMAGE_SVG;
  }else if(strcmp(content_type, "image/x-icon") == 0){
    return IMAGE_ICO;
  }else if(strcmp(content_type, "application/json") == 0){
    return APPLICATION_JSON;
  }else if(strcmp(content_type, "application/xml") == 0){
    return APPLICATION_XML;
  }else if(strcmp(content_type, "application/pdf") == 0){
    return APPLICATION_PDF;
  }else if(strcmp(content_type, "application/zip") == 0){
    return APPLICATION_ZIP;
  }else if(strcmp(content_type, "application/octet-stream") == 0){
    return APPLICATION_OCTET_STREAM;
  }
  return -1;
}

const int str_hash(const char*  str){
  int hash = 0;
  int i;
  int len = strlen(str);
  for(i = 0; i < len; i++){
    hash += str[i];
  }
  for(i = 0; i < len; i+=2){
    if(i + 1 < len){
      hash *= str[i] * str[i + 1];
    }
  }
  return hash;
}


typedef struct request_s{
  char* method;
  char* url;
  char* version;
  char* headers;
  char* body;
  char* raw_body;
  int status_code;
  char* content_type;
} request_t;

int str_includes(char* input,const char* match){
  int input_len = strlen(input);
  int match_len = strlen(match);
  int i, j;
  for(i = 0; i < input_len; i++){
    if(input[i] == match[0]){
      for(j = 0; j < match_len; j++){
        if(input[i + j] != match[j]){
          break;
        }
      }
      if(j == match_len){
        return 1;
      }
    }
  }
  return 0;
}
void parse_response(request_t* request, char* buffer){
  char* request_split = strtok(buffer, "\n");
  printf("Request: %s\n", request_split);

  char* method = strtok(request_split, " ");
  char* url = strtok(NULL, " ");
  char* http_version = strtok(NULL, " ");
  printf("HTTP Version: %s\n", http_version);
  printf("Method: %s\n", method);
  printf("URL: %s\n", url);
}
void create_response(int status_code, content_type_t content_type, request_method_t method, char* buffer, char* body){
  char* http_version = "HTTP/1.1 ";
  strcat(buffer, http_version);// Ex: HTTP/1.1
  char* status_code_str = malloc(3);
  sprintf(status_code_str,"%d ", status_code);
  strcat(buffer, status_code_str); // Ex: 200
  strcat(buffer, get_status_code_message(status_code)); // Ex: OK
  strcat(buffer, "\n");
  strcat(buffer, "Content-Type: ");
  strcat(buffer, get_content_type_str(content_type));


}
int main(){
  int port = 6900;
  int server_fd, new_socket;
  struct sockaddr_in server_addr;
  int opt = 1;
  int addrelen = sizeof(server_addr);
  char buffer[1024] = {0};
  char *header_prefix = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";

  if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  
  if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port);

  if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if(listen(server_fd, 3) < 0){
    perror("listen");
    exit(EXIT_FAILURE);
  }


  while (1) {
    printf("Waitin' for some peeps...\n");

    if((new_socket = accept(server_fd, (struct sockaddr *)&server_addr, (socklen_t*)&addrelen)) < 0){
      perror("accept");
      exit(EXIT_FAILURE);
    }

    read(new_socket, buffer, 1024);

    char* response_buffer = (char*)calloc(1024, sizeof(char));

    strcat(response_buffer, header_prefix);

    request_t* request = (request_t*)malloc(sizeof(request_t));
    parse_response(request,buffer);

    send(new_socket, response_buffer, strlen(response_buffer), 0);

    printf("Sent!\n %s", response_buffer);

    free(response_buffer);
    free(request);
    close(new_socket);
  }

  return 0;


}

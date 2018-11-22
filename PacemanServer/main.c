/* Servidor y logica de PACE MAN */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "MovimientoJugador.c"


struct EntityStruct{

    int x;
    int y;
    char* direction;
    int lives;

}EntityStruct;





int sockfd;
int newsockfd;
int portno = 9000; /**< numero del puerto a utilizar paral a conexion */

socklen_t clilen;
char buffer[256]; /**< buffer que se usa para enviar y recibir mensajes */

struct sockaddr_in serv_addr, cli_addr;

int n;

struct EntityStruct player = { 15, 14, " ", 3};

struct EntityStruct redGhost = { 8, 14, "r", 0};

struct EntityStruct blueGhost = { 8, 14, " ", 0};

struct EntityStruct yellowGhost = { 8, 14, " ", 0};

struct EntityStruct pinkGhost = { 8, 14, " ", 0};



/** mapa del juego. cada numero representa un tipo de entidad
 * 1 : se refiere a las paredes del mapa
 * 2 : se refiere a los orbes que otorgan puntos al pasar por ellos
 * 3 : casilla donde se encuentra el jugador
 * 4 : se refiere al fantasma rojo  */

int map[20][29] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                   {1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1},
                   {1,2,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,2,1},
                   {1,2,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,2,1},
                   {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                   {1,2,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,2,1},
                   {1,2,2,2,2,2,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,2,2,2,2,2,1},
                   {1,2,1,1,1,2,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,2,1,1,1,2,1},
                   {1,2,1,1,1,2,1,1,0,0,0,0,0,0,4,0,0,0,0,0,0,1,1,2,1,1,1,2,1},
                   {1,2,2,2,2,2,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,2,2,2,2,2,1},
                   {1,2,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,2,1},
                   {1,2,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,2,1},
                   {1,2,1,1,1,2,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,2,1,1,1,2,1},
                   {1,2,2,2,2,2,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,2,2,2,2,2,1},
                   {1,2,1,1,1,2,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,2,1,1,1,2,1},
                   {1,2,1,1,1,2,2,2,2,2,2,2,2,2,3,2,2,2,2,2,2,2,2,2,1,1,1,2,1},
                   {1,2,1,1,1,2,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,2,1,1,1,2,1},
                   {1,2,1,1,1,2,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,2,1,1,1,2,1},
                   {1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1},
                   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};





/** muestra errores provenientes de las operaciones con sockets */

void error(char *msg)
{
    perror(msg);
    exit(1);
}


/** envia el mensaje a traves del socket */

void sendMessage(char* message)
{




    n = write(newsockfd,message, strlen(message));

    printf("mensaje enviado: %s", message);

    if (n < 0)
        error("ERROR writing to socket");


    //close(newsockfd);
    //close(sockfd);

}



/** se encarga de analizar el mensaje que viene desde el cliente */

void messageIdentifier(char* buffer)
{

    char splitStrings[10][10]; //can store 10 words of 10 characters
    int i,j,cnt;


    j=0; cnt=0;
    for(i=0;i<=(strlen(buffer));i++)
    {
        // if space or NULL found, assign NULL into splitStrings[cnt]
        if(buffer[i]==' '||buffer[i]=='\0')
        {
            splitStrings[cnt][j]='\0';
            cnt++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            splitStrings[cnt][j]=buffer[i];
            j++;
        }
    }
    //printf("\nOriginal String is: %s",buffer);
    //printf("\nStrings (words) after split by space:\n");

    /*for(i=0;i < cnt;i++)
        printf("%s\n",splitStrings[i]);


    printf("voy a analizar el mensaje \n");

   */

    /** ****************************
     *  *************   MOVIMIENTOS **********************************
     * ************************************/


    /** **************** Movimiento del  Jugador ********************/


    if(strncmp(splitStrings[0], "player", 6) == 0)
    {

        /** **************** Direccion del Jugador ********************/

        if (strncmp(splitStrings[1], "direction", 9) == 0)
        {

            /** **************** Direccion derecha ********************/

            if(strncmp(splitStrings[2], "r", 1) ==0 )
            {

            char * msg = "cambiando direccion a derecha \n";

            printf("cambiando direccion a derecha \n");

            player.direction = "r";



            sendMessage(msg);

            }

            /** **************** Direccion izquierda ********************/

            if(strncmp(splitStrings[2], "l", 1) ==0 )
            {

            char * msg = "cambiando direccion a izquierda \n";

            printf("cambiando direccion a izquierda \n");

            player.direction = "l";



            sendMessage(msg);

            }


            /** **************** Direccion arriba ********************/

            if(strncmp(splitStrings[2], "u", 1) ==0 )
            {

            char * msg = "cambiando direccion a arriba \n";

            printf("cambiando direccion a arriba \n");

            player.direction = "u";



            sendMessage(msg);

            }

            /** **************** Direccion abajo ********************/

            if(strncmp(splitStrings[2], "d", 1) ==0 )
            {

            char * msg = "cambiando direccion a abajo \n";

            printf("cambiando direccion a abajo \n");

            player.direction = "d";



            sendMessage(msg);

            }

        }

       /** ****************************
         *  *************   Movimiento del jugador **********************************
         * ************************************/


        if (strncmp(splitStrings[1], "move", 4) == 0)
        {

            /** movimiento hacia la derecha ******************************************************************************/

            if( strncmp(player.direction, "r", 1) == 0)
            {
                if(map[player.x][player.y+1] != 1){


                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);
                    //printf( "el mapa dice adelante: %i \n", map[player.x][player.y+1]);



                    map[player.x][player.y] = 0;
                    ++player.y;
                    map[player.x][player.y] = 3;

                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);

                    char message[64] = "player move";

                    char numero[4];
                    sprintf(numero, " %d", player.x);

                    strcat(message, numero);

                    sprintf(numero, " %d", player.y);

                    strcat(message, numero);
                    strcat(message, " \n");

                    char* msg = message;

                    //printf("voy a enviar este movimiento: %s", msg);

                    sendMessage(msg);
                }



            }

            /** movimiento hacia la izquierda ******************************************************************************/

            if( strncmp(player.direction, "l", 1) == 0)
            {
                if(map[player.x][player.y-1] != 1){


                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);
                    //printf( "el mapa dice adelante: %i \n", map[player.x][player.y-1]);



                    map[player.x][player.y] = 0;
                    --player.y;
                    map[player.x][player.y] = 3;

                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);

                    char message[64] = "player move";

                    char numero[4];
                    sprintf(numero, " %d", player.x);

                    strcat(message, numero);

                    sprintf(numero, " %d", player.y);

                    strcat(message, numero);
                    strcat(message, " \n");

                    char* msg = message;

                    //printf("voy a enviar este movimiento: %s", msg);

                    sendMessage(msg);
                }




            }
            /** movimiento hacia la arriba ******************************************************************************/

            if( strncmp(player.direction, "u", 1) == 0)
            {
                if(map[player.x-1][player.y] != 1){


                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);
                    //printf( "el mapa dice adelante: %i \n", map[player.x-1][player.y]);



                    map[player.x][player.y] = 0;
                    --player.x;
                    map[player.x][player.y] = 3;

                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);

                    char message[64] = "player move";

                    char numero[4];
                    sprintf(numero, " %d", player.x);

                    strcat(message, numero);

                    sprintf(numero, " %d", player.y);

                    strcat(message, numero);
                    strcat(message, " \n");

                    char* msg = message;

                   // printf("voy a enviar este movimiento: %s", msg);

                    sendMessage(msg);
                }



            }

            /** movimiento hacia la abajo ******************************************************************************/

            if( strncmp(player.direction, "d", 1) == 0)
            {
                if(map[player.x+1][player.y] != 1){


                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);
                    //printf( "el mapa dice adelante: %i \n", map[player.x+1][player.y]);



                    map[player.x][player.y] = 0;
                    ++player.x;
                    map[player.x][player.y] = 3;

                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);

                    char message[64] = "player move";

                    char numero[4];
                    sprintf(numero, " %d", player.x);

                    strcat(message, numero);

                    sprintf(numero, " %d", player.y);

                    strcat(message, numero);
                    strcat(message, " \n");

                    char* msg = message;

                   // printf("voy a enviar este movimiento: %s", msg);

                    sendMessage(msg);
                }


            }


            else{



                char message[64] = "player move";

                char numero[4];
                sprintf(numero, " %d", player.x);

                strcat(message, numero);

                sprintf(numero, " %d", player.y);

                strcat(message, numero);
                strcat(message, " \n");

                char* msg = message;

               // printf("voy a enviar este movimiento: %s", msg);

                sendMessage(msg);

            }

        }

    }









    /** **************** Movimiento del  los enemigos *******************
     *   ****************************************************************/


    if(strncmp(splitStrings[0], "enemy", 5) == 0)
    {
        /** **************** Direccion del Jugador ********************/

        if (strncmp(splitStrings[1], "direction", 9) == 0)
        {

            /** **************** Direccion derecha ********************/

            if(strncmp(splitStrings[2], "r", 1) ==0 )
            {

            char * msg = "derecha \n";



            if (strncmp(splitStrings[3], "red", 3) == 0){
                redGhost.direction = "r";
            }

            if (strncmp(splitStrings[3], "blue", 4) == 0){
                blueGhost.direction = "r";
            }

            if (strncmp(splitStrings[3], "yellow", 6) == 0){
                yellowGhost.direction = "r";
            }

            if (strncmp(splitStrings[3], "pink", 4) == 0){
                pinkGhost.direction = "r";
            }


            sendMessage(msg);

            }

            /** **************** Direccion izquierda ********************/

            if(strncmp(splitStrings[2], "l", 1) ==0 )
            {

            char * msg = "izquierda \n";



            if (strncmp(splitStrings[3], "red", 3) == 0){
                redGhost.direction = "l";
            }

            if (strncmp(splitStrings[3], "blue", 4) == 0){
                blueGhost.direction = "l";
            }

            if (strncmp(splitStrings[3], "yellow", 6) == 0){
                yellowGhost.direction = "l";
            }

            if (strncmp(splitStrings[3], "pink", 4) == 0){
                pinkGhost.direction = "l";
            }



            sendMessage(msg);

            }


            /** **************** Direccion arriba ********************/

            if(strncmp(splitStrings[2], "u", 1) ==0 )
            {

            char * msg = "arriba \n";



            if (strncmp(splitStrings[3], "red", 3) == 0){
                redGhost.direction = "u";
            }

            if (strncmp(splitStrings[3], "blue", 4) == 0){
                blueGhost.direction = "u";
            }

            if (strncmp(splitStrings[3], "yellow", 6) == 0){
                yellowGhost.direction = "u";
            }

            if (strncmp(splitStrings[3], "pink", 4) == 0){
                pinkGhost.direction = "u";
            }



            sendMessage(msg);

            }

            /** **************** Direccion abajo ********************/

            if(strncmp(splitStrings[2], "d", 1) ==0 )
            {

            char * msg = "abajo \n";



            if (strncmp(splitStrings[3], "red", 3) == 0){
                redGhost.direction = "d";
            }

            if (strncmp(splitStrings[3], "blue", 4) == 0){
                blueGhost.direction = "d";
            }

            if (strncmp(splitStrings[3], "yellow", 6) == 0){
                yellowGhost.direction = "d";
            }

            if (strncmp(splitStrings[3], "pink", 4) == 0){
                pinkGhost.direction = "d";
            }



            sendMessage(msg);

            }

        }
    }


    /**  MOVIMIENTO DE LOS ENEMIGOS *******************************************************************/


    if (strncmp(splitStrings[1], "move", 4) == 0)
    {



        /**  MOVIMIENTO DEL ENEMIGO ROJO *******************************************************************/



        if (strncmp(splitStrings[2], "red", 3) == 0)
        {

            /** movimiento hacia la derecha ******************************************************************************/


            if( strncmp(redGhost.direction, "r", 1) == 0)
            {
                if(map[redGhost.x][redGhost.y+1] != 1){


                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);
                    //printf( "el mapa dice adelante: %i \n", map[player.x][player.y+1]);



                    map[redGhost.x][redGhost.y] = 0;
                    ++redGhost.y;
                    map[redGhost.x][redGhost.y] = 4;

                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);

                    char message[64] = "enemy move red";

                    char numero[4];
                    sprintf(numero, " %d", redGhost.x);

                    strcat(message, numero);

                    sprintf(numero, " %d", redGhost.y);

                    strcat(message, numero);
                    strcat(message, " \n");

                    char* msg = message;

                    printf("voy a enviar este movimiento: %s", msg);

                    sendMessage(msg);
                }



            }

            /** movimiento hacia la izquierda ******************************************************************************/

            if( strncmp(redGhost.direction, "l", 1) == 0)
            {
                if(map[redGhost.x][redGhost.y-1] != 1){


                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);
                    //printf( "el mapa dice adelante: %i \n", map[player.x][player.y-1]);



                    map[redGhost.x][redGhost.y] = 0;
                    --redGhost.y;
                    map[redGhost.x][redGhost.y] = 4;

                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);

                    char message[64] = "enemy move red";

                    char numero[4];
                    sprintf(numero, " %d", redGhost.x);

                    strcat(message, numero);

                    sprintf(numero, " %d", redGhost.y);

                    strcat(message, numero);
                    strcat(message, " \n");

                    char* msg = message;

                    printf("voy a enviar este movimiento: %s", msg);

                    sendMessage(msg);
                }




            }
            /** movimiento hacia la arriba ******************************************************************************/

            if( strncmp(redGhost.direction, "u", 1) == 0)
            {
                if(map[redGhost.x-1][redGhost.y] != 1){


                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);
                    //printf( "el mapa dice adelante: %i \n", map[player.x-1][player.y]);



                    map[redGhost.x][redGhost.y] = 0;
                    --redGhost.x;
                    map[redGhost.x][redGhost.y] = 4;

                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);

                    char message[64] = "enemy move red";

                    char numero[4];
                    sprintf(numero, " %d", redGhost.x);

                    strcat(message, numero);

                    sprintf(numero, " %d", redGhost.y);

                    strcat(message, numero);
                    strcat(message, " \n");

                    char* msg = message;

                    printf("voy a enviar este movimiento: %s", msg);

                    sendMessage(msg);
                }



            }

            /** movimiento hacia la abajo ******************************************************************************/

            if( strncmp(player.direction, "d", 1) == 0)
            {
                if(map[player.x+1][player.y] != 1){


                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);
                    //printf( "el mapa dice adelante: %i \n", map[player.x+1][player.y]);



                    map[redGhost.x][redGhost.y] = 0;
                    ++redGhost.x;
                    map[redGhost.x][redGhost.y] = 4;

                    //printf( "el jugador esta en: %i , %i \n", player.x, player.y);
                    //printf( "el mapa dice: %i \n", map[player.x][player.y]);

                    char message[64] = "enemy move red";

                    char numero[4];
                    sprintf(numero, " %d", redGhost.x);

                    strcat(message, numero);

                    sprintf(numero, " %d", redGhost.y);

                    strcat(message, numero);
                    strcat(message, " \n");

                    char* msg = message;

                    printf("voy a enviar este movimiento: %s", msg);

                    sendMessage(msg);
                }


            }


            else{



                char message[64] = "choque";

                char numero[4];
                sprintf(numero, " %d", redGhost.x);

                strcat(message, numero);

                sprintf(numero, " %d", redGhost.y);

                strcat(message, numero);
                strcat(message, " \n");

                char* msg = message;

                printf("voy a enviar este movimiento: %s", msg);

                sendMessage(msg);

            }


        }



    }




}






void readMessage()
{
    bzero(buffer,256);

    n = read(newsockfd,buffer,255);




    if (n < 0)
        error("ERROR reading from socket");

    printf("Here is the message: %s\n",buffer);


    messageIdentifier(buffer);



}





void connectServer()
{


    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");


    while (true)
    {


    listen(sockfd,5);

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsockfd < 0)
         error("ERROR on accept");

    readMessage();

    }
}



void ServerSocket()
{




    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
       error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);


}


int main()
{





    ServerSocket();


    connectServer();



    /*


    printf("trying to set up the server ... \n\n");

     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0)
        error("ERROR opening socket \n");


     printf("server is running! \n");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = 9000;
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
     {
        error("ERROR on binding");
     }

     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

     if (newsockfd < 0)
          error("ERROR on accept");

     bzero(buffer,256);
     n = read(newsockfd,buffer,255);

     if (n < 0)
         error("ERROR reading from socket");


     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);

     if (n < 0)
         error("ERROR writing to socket");


      */

     return 0;


}




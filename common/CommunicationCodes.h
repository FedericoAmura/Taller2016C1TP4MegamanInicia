#ifndef SRC_COMMUNICATIONCODES_H_
#define SRC_COMMUNICATIONCODES_H_

/* Protocolo de comunicacion
 * se envian los mensajes terminados por un '\n'
 * con los codigos separados por un espacio*/

//OPERATION CODES client->server
#define KEYBOARD_STATE 1
#define SELECT_LEVEL 2
#define ERROR 90
#define CLIENT_DISCONNECTED 99

//OPERATION CODES server->client
#define HELLO 0
#define CLIENTS_CONNECTED 10
#define DRAW 1
#define REDRAW 2
#define MOVE 3
#define KILL 4
#define SOUND 5
#define START_LEVEL_SCREEN 6
#define BACK_TO_LEVEL_SELECTION 7
#define LIFE_STATUS 8
#define LEVEL_STATUS 9
#define SERVER_DISCONNECTED 99

//LEVEL CODES
#define MAGNETMAN 1001
#define SPARKMAN 1002
#define RINGMAN 1003
#define FIREMAN 1004
#define BOMBMAN 1005

//KEYBOARD_STATE codes
/* Ver MegamanBeginsConstants-KEY IDS para los Ids de cada tecla
 * Se manda el estado del teclado en el cliente
 * El estado del teclado es la sumatoria de los IDs de las teclas apretadas
 * formato: "KEYBOARD_STATE keyboardState\n"
 * ej: "1 14\n" son las teclas UP+RIGHT+DOWN (2+4+8=14)
 * */

//SELECT_LEVEL codes
/* Se manda el codigo del nivel elegido por el cliente
 * formato: "SELECT_LEVEL levelCode\n"
 * ej: "2 1005\n" es seleccionar nivel BOMBMAN
 * */

//ERROR codes
/* Se manda para notificar un error
 * formato: "ERROR detalle\n"
 * ej: "90 DrawableID no encontrado\n"
 * */

//HELLO codes
/* se manda seguido del numero de jugador asignado
 * formato: "HELLO numCliente\n"
 * ej: "0 1\n" Sos el cliente 1
 * */

//CLIENTS_CONNECTED codes
/* se manda seguido de la cantidad de jugadores conectados
 * formato: "CLIENTS_CONNECTED numClientes\n"
 * ej: "10 3\n" hay 3 clientes conectados
 * */

//DRAW codes
/* Se manda el id del dibujable, seguido del codigo del sprite correspondiente,
 * su sentido y su posicion. Se usa para nuevos dibujables.
 * formato: "DRAW id idSprite flipped posX pos\n"
 * ej: "1 5 9000 0 10 20\n" dibujar el dibujable 5 como un megamanIddle sin
 * flippear en pos X:10-Y:20
 * */

//REDRAW codes
/* Se manda el id del dibujable, seguido del codigo del nuevo sprite y si va
 * invertido. Se usa para cambiar el dibujo.
 * formato: "REDRAW id idSprite flipped"
 * ej: "2 5 9000 1\n" redibujar el dibujable 5 como megamanIddle pero flippeado
 * */

//MOVE codes
/* Se manda el id del dibujable, seguido de su posicion
 * formato: "MOVE id posX posY"
 * ej: "3 5 14 22\n" mover el dibujable 5 a pos X:14-Y:22
 * */

//KILL codes
/* Se manda id del dibujable para que se borre de pantalla
 * formato: "KILL idSprite"
 * ej: "4 5\n" borrar dibujable 5
 * */

//SOUND codes
#define DISPARO 1
/* Se manda el codigo del ruido correspondiente
 * formato: "SOUND idSound\n"
 * ej: "5 1\n" para reproducir el ruido de disparo
 * */

//START_LEVEL_SCREEN codes
/* Se manda para notificar el inicio de un nivel, seguido del cod de nivel
 * formato: "START_LEVEL_SCREEN levelCode\n"
 * ej: "6 1001\n" y el cliente cambia al modo nivel MAGNETMAN
 * */

//BACK_TO_LEVEL_SELECTION codes
/* Se manda para notificar el fin de un nivel y vuelta a la seleccion de estos
 * formato: "BACK_TO_LEVEL_SELECTION\n"
 * ej: "7\n" y el cliente cambia al modo seleccion de nivel
 * */

//LIFE_STATUS codes
/* Se manda para notificar el cambio de estado de salud de un jefe (0) o un jugador(1-4)
 * formato: "LIFE_STATUS idPersonaje porcentajeSalud\n"
 * ej: "8 0 25\n" para indicar que el jefe esta al 25% de su salud
 * */

//LEVEL_STATUS codes
/* Se manda para notificar el estado de los niveles, es decir, cuando se los gana
 * formato: "LEVEL_STATUS levelCode estado\n"
 * ej: "9 1002 1\n" para indicar que se le gano(1) a SparkMan(1002)
 * */

#endif /* SRC_COMMUNICATIONCODES_H_ */

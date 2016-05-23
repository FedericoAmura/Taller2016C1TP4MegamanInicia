#ifndef SRC_CLIENTKEYCODES_H_
#define SRC_CLIENTKEYCODES_H_

/* Protocolo de comunicacion
 * se envian los mensajes terminados por un '\n'
 * con los codigos separados por un espacio*/

//operation codes
#define KEY_PRESSED 1
#define SELECT_LEVEL 2
#define DRAW 3
#define KILL 4
#define COLLISION 5
#define BACK_TO_LEVEL_SELECTION 6
#define END_CURRENT 9 //PARA DECIR QUE TERMINO EL ENVIO, EJ: DIBUJAR TODOS LOS SPRITES

//key codes
#define KEY_UP 2
#define KEY_RIGHT 3
#define KEY_DOWN 4
#define KEY_LEFT 5
#define KEY_SPACE 6
#define KEY_ESC 7
/*ej: "1 2\n" es tecla apretada arriba*/

/*level codes
 * mandar el codigo del jefe correspondiente
 *ej: "2 1005\n" es seleccionar nivel BOMBMAN*/

/*draw codes
 * se manda el codigo del sprite correspondiente, seguido de su posicion
 * ej: "3 9000 X:10 Y:20 \n" dibujar megaman en pos X:10-Y:20*/

#endif /* SRC_CLIENTKEYCODES_H_ */

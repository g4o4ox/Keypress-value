#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

struct termios orig_termios;

void disableRwMode(){
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig_termios);
}

void enableRwMode(){
	
	tcgetattr(STDIN_FILENO,&orig_termios);
	atexit(disableRwMode); // atexit() serve para registrar o disablerwmode e ser chamada quando o programa termina
			       	



	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw); // faz a leitura dos atributos atuais em uma estrutura
	raw.c_lflag &= ~(ECHO |	ICANON ); // ECHO faz com que todas as chaves sejam impressas no terminal
					  // Inserindo o ICANON desliga o modo canonico, agora o programa le o input byte por byte em vez de linha por linha
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); 
}



int main(){

	enableRwMode();
	char c;
	while (read(STDIN_FILENO,&c, 1) == 1 && c != 'q'){
		if(iscntrl(c)){ // iscntrl 
			printf("%b\n",c);
		} else { printf("%b ('%c')\n", c,c);} 

	}
	return 0;

}

#include <cli.h>

static struct termios term, oterm;

// https://stackoverflow.com/questions/62895595/how-i-can-get-input-without-press-enter-end-without-see-the-input-on-screen

int getch(void)
{
    int c = 0;

    //get the information of the terminal assosiated with stdin and store in oterm
    tcgetattr(0, &oterm);

    //copy oterm in term
    memcpy(&term, &oterm, sizeof(term));

    //Abilite ICANON mode to enable more functionalities
    // Active ECHO
    term.c_lflag &= ~(ICANON | ECHO);
    //Min character for noncanonical red
    term.c_cc[VMIN] = 1;
    //  Timeout in deciseconds for noncanonical read (TIME
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    c = getchar();
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}
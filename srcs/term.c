#include "../twenty.h"

int		init(void)		//EXECUTION
{
	char				*name_term;
	struct termios		term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag |= (ECHO);
	term.c_lflag |= (ICANON);
	// term.c_cc[VEOF] = 3;
	// term.c_cc[VINTR] = 4;
	term.c_cc[VEOF] = 4;
	term.c_cc[VINTR] = 3;

	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (1);
}

int		set_up_term(void) ///TERMINAL
{
	char	*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_lflag |= (ISIG);
	term.c_cc[VEOF] = 3;
	term.c_cc[VINTR] = 4;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (1);
}

int		set_up_term_prompt(void) ///TERMINAL_PROMPT_SPECIAL
{
	char	*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	// term.c_cc[VEOF] = 3;
	// term.c_cc[VINTR] = 4;
	term.c_cc[VEOF] = 4;
	term.c_cc[VINTR] = 3;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (-1);
	return (1);
}
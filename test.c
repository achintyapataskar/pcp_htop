#include "process.h"
#include "display.h"
#include <unistd.h>


int main() {

	init_linklist(&process_list);
	init_window();


	process p;
	int ch, flag;

	flag = 0;
	while(1) {
		ch = getch();
		if(ch != ERR)
			flag = ch;
		if(ch == 'q')
			break;

		customize_display(flag);


		create_process(&p, rand() % 5000, rand() % 100, rand() % 100, "name", "cmd");


		add_node_to_linklist(&process_list, &p);


		sort_and_display(ch, &process_list);



		move(0, 0);
		sleep(1);
	}
	close_window();
	return 0;
}

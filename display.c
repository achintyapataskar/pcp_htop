#include "process.h"
#include "display.h"


extern int display_size;
void init_window() {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	//wresize(stdscr, 25, 70);
}
void close_window() {
	refresh();
	getch();
	endwin();
}
void customize_display(char ch) {
	switch(ch) {
		case 'p': printw("^PID  User      Command  MEM   CPU\n");
				  break;
		case 'c': printw("PID   User      Command  MEM   ^CPU\n");
				  break;
		case 'm': printw("PID   User      Command  ^MEM   CPU\n");
				  break;
		default : printw("PID   User      Command  MEM   CPU\n");
	}
}
void sort_and_display(char ch, linklist *l) {
		int row, col;
		switch(ch) {
			case 'p': linklist_sort_process(l);
					break;
			case 'c':	linklist_sort_cpu(l);
					break;
			case 'm':	linklist_sort_mem(l);
					break;
			default: linklist_no_sort();
		}
		print_top_n_linklist(l, DISPLAY_SIZE);
		printw("\n");
		getmaxyx(stdscr, row, col);
		move(row - 1, 0);
		printw("p - Sort on process ID c - Sort on CPU Usage m - Sort on Memory Usage q - Quit");
		refresh();
}

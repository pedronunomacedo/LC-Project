#include <lcom/lcf.h>
#include <lcom/proj.h>

int main(int argc, char *argv[]) {
	lcf_set_language("EN-US");
	lcf_trace_calls("/home/lcom/labs/proj/trace.txt");
	lcf_log_output("/home/lcom/labs/proj/output.txt");
	if (lcf_start(argc, argv) != OK) return !OK;
	return lcf_cleanup();
}

int (proj_main_loop)(int argc, char *argv[]) {
	printf("To implement\n");
	return !OK;
}

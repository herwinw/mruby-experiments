#include <stdio.h>

#include <mruby.h>
#include <mruby/compile.h>

int main(int argc, const char **argv) {
	FILE *f;
	mrb_state *mrb = mrb_open();
	if (!mrb) return 1;
	if (!(f = fopen("hello.rb", "r"))) return 1;
	mrb_load_file(mrb, f);
	fclose(f);
	mrb_funcall(mrb, mrb_top_self(mrb), "hello", 1, mrb_str_new_cstr(mrb, "fly"));
	mrb_close(mrb);
	return 0;
}

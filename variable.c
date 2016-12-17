#include <stdio.h>

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>
#include <mruby/variable.h>

int main (int argc, const char **argv) {
	FILE *f;
	mrb_state *mrb = mrb_open();
	mrb_sym sym;
	if (!mrb) return 1;

	if (!(f = fopen("variable.rb", "r"))) return 1;
	mrb_load_file(mrb, f);
	fclose(f);

	sym = mrb_intern_cstr(mrb, "$global");

	mrb_gv_set(mrb, sym, mrb_str_new_cstr(mrb, "wello"));

	mrb_funcall(mrb, mrb_top_self(mrb), "hello", 1, mrb_gv_get(mrb, sym));

	mrb_gv_remove(mrb, sym);
	mrb_funcall(mrb, mrb_top_self(mrb), "hello", 1, mrb_str_new_cstr(mrb, "wups"));

	mrb_close(mrb);
	return 0;
}

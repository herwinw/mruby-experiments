#include <stdio.h>

#include <mruby.h>
#include <mruby/compile.h>

int main (int argc, const char **argv) {
	FILE *f;
	mrb_value val, expect;
	mrb_sym expect2;
	mrb_state *mrb = mrb_open();
	if (!mrb) return 1;
	if (!(f = fopen("int.rb", "r"))) return 1;
	mrb_load_file(mrb, f);
	fclose(f);

	val = mrb_funcall(mrb, mrb_top_self(mrb), "hello", 1, mrb_str_new_cstr(mrb, "fly"));
	expect = mrb_fixnum_value(1);
	if (mrb_equal(mrb, val, expect)) {
		printf("Equal\n");
	} else {
		printf("Not equal\n");
	}

	val = mrb_funcall(mrb, mrb_top_self(mrb), "get_symbol", 1, mrb_str_new_cstr(mrb, "foo"));
	expect2 = mrb_intern_cstr(mrb , "foo");
	if (mrb_obj_to_sym(mrb, val) == expect2) {
		printf("Equal\n");
	} else {
		printf("Not equal\n");
	}

	mrb_close(mrb);
	return 0;
}

#include <stdio.h>

#include <mruby.h>
#include <mruby/compile.h>

int main (int argc, const char **argv) {
	FILE *f;
	mrb_value val;
	int i;
	mrb_state *mrb = mrb_open();
	if (!mrb) return 1;
	if (!(f = fopen("return.rb", "r"))) return 1;
	mrb_load_file(mrb, f);
	fclose(f);

	val = mrb_funcall(mrb, mrb_top_self(mrb), "return_int", 0);
	switch (mrb_type(val)) {
		case MRB_TT_FIXNUM:
			i = mrb_int(mrb, val);
			printf("Returned a fixnum: %i\n", i);
			break;
		case MRB_TT_ARRAY:
			printf("Returned an array\n");
			break;
		default:
			printf("Unlisted return type\n");
			break;
	}

	val = mrb_funcall(mrb, mrb_top_self(mrb), "return_array", 0);
	switch (mrb_type(val)) {
		case MRB_TT_FIXNUM:
			printf("Returned a fixnum\n");
			break;
		case MRB_TT_ARRAY:
			printf("Returned an array\n");
			break;
		default:
			printf("Unlisted return type\n");
			break;
	}

	val = mrb_funcall(mrb, mrb_top_self(mrb), "return_nil", 0);
	switch (mrb_type(val)) {
		case MRB_TT_FIXNUM:
			printf("Returned a fixnum\n");
			break;
		case MRB_TT_ARRAY:
			printf("Returned an array\n");
			break;
		default:
			printf("Unlisted return type\n");
			break;
	}

	mrb_close(mrb);
	return 0;
}

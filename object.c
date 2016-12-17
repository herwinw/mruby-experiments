#include <stdio.h>

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/string.h>
#include <mruby/variable.h>

static mrb_value example_method(mrb_state *mrb, mrb_value self) {
	mrb_int i;
	char *str = NULL;

	mrb_get_args(mrb, "iz", &i, &str);
	fprintf(stderr, "Example method called with param %s and level %i\n", str, i);

	return mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "val"));
}

int main (int argc, const char **argv) {
	FILE *f;
	mrb_state *mrb = mrb_open();
	mrb_value obj;
	if (!mrb) return 1;

	struct RClass *example_module;
	example_module = mrb_define_module(mrb, "Example_Module");

	struct RClass *example_class;
	example_class = mrb_define_class_under(mrb, example_module, "Example_Class", mrb->object_class);
	mrb_define_method(mrb, example_class, "example_method", example_method, MRB_ARGS_REQ(2));

	obj = mrb_obj_new(mrb, example_class, 0, NULL);
	mrb_iv_set(mrb, obj, mrb_intern_cstr(mrb, "val"), mrb_fixnum_value(123));

	if (!(f = fopen("object.rb", "r"))) return 1;
	mrb_load_file(mrb, f);
	fclose(f);

	mrb_funcall(mrb, mrb_top_self(mrb), "hello", 1, obj);

	mrb_close(mrb);
	return 0;
}

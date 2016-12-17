#include <stdio.h>

#include <mruby.h>
#include <mruby/compile.h>

int main (int argc, const char **argv) {
	FILE *f;
	struct RClass * module;
	mrb_state *mrb = mrb_open();
	if (!mrb) return 1;

	if (!(f = fopen("module.rb", "r"))) return 1;
	mrb_load_file(mrb, f);
	fclose(f);

	module = mrb_module_get(mrb, "Foo");
	if (module == NULL) {
		fprintf(stderr, "Unable to get module");
		return 1;
	}

	mrb_funcall(mrb, mrb_top_self(mrb), "bar", 0);

	mrb_close(mrb);
	return 0;
}

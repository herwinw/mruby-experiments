#include <stdio.h>

#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/array.h>
#include <mruby/hash.h>

int main (int argc, const char **argv) {
	FILE *f;
	mrb_state *mrb = mrb_open();
	mrb_value ary, hsh;
	if (!mrb) return 1;
	if (!(f = fopen("array.rb", "r"))) return 1;
	mrb_load_file(mrb, f);
	fclose(f);

	ary = mrb_ary_new_capa(mrb, 10);
	for (int i=0; i<10; i++) {
		mrb_value tmp = mrb_ary_new_capa(mrb, 2);
		mrb_ary_push(mrb, tmp, mrb_str_new_cstr(mrb, "Key"));
		mrb_ary_push(mrb, tmp, mrb_fixnum_value(i));
		mrb_ary_push(mrb, ary, tmp);
	}
	mrb_funcall(mrb, mrb_top_self(mrb), "hello", 1, ary);

	hsh = mrb_hash_new(mrb);
	mrb_hash_set(mrb, hsh, mrb_str_new_cstr(mrb, "one"), mrb_fixnum_value(1));
	mrb_hash_set(mrb, hsh, mrb_str_new_cstr(mrb, "two"), mrb_fixnum_value(2));
	mrb_funcall(mrb, mrb_top_self(mrb), "hello", 1, mrb_ary_splat(mrb, hsh));

	ary = mrb_assoc_new(mrb, mrb_str_new_cstr(mrb, "one"), mrb_fixnum_value(1));
	mrb_funcall(mrb, mrb_top_self(mrb), "hello", 1, ary);

	mrb_close(mrb);
	return 0;
}

#!/usr/bin/env mruby

module Foo
	def self.bar
		p "Hello world from Foo.bar"
	end
end

def bar
	p "This is the wrong bar"
end

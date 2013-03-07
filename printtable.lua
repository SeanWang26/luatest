--require "print_r"
--require "stable"

a = {}
 
a.a = { 
	hello = { 
		alpha = 1 ,
		beta = 2,
	},
	world =  {
		foo = "ooxx",
		bar = "haha",
		root = a,
	},
}
a.b = { 
	test = a.a 
}
a.c = a.a.hello

print("i am here")

print("length", #1)

--stable._functest(1,2,3)
--print_r(stable)

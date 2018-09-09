for number in range(30):
	print("ADD_TINY_TEST(test_" + str(number) + "){")
	print("	int i = rand()%50;")
	print("	PRINT(\"%d\" NEWLINE, i);")
	print("	ASSERT_TEST_RESULT(i != " + str(number) + ");")
	print("}\r\n")

# for number in range(100):
# 	print("	RUN_TINY_TEST(test_" + str(number) + ");")
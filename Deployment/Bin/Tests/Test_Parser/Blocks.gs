CLASS class Big
	ENABLE_PUBLIC
	FUNC void foo()
		BLOCK
			VAR double a = 10.0;
			STATE print(a);
		STATE print("Hello");
FUNC int main()
	BLOCK
		VAR int l1;
		BLOCK
			VAR int l2;
			BLOCK
				VAR int l3;
				BLOCK
					VAR int l4;
			BLOCK
				VAR int r3;
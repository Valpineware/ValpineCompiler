void someOp(int a, int b);
int add(int a, int b);
void someOp(int a, int b)
{
	add(a, b);
}
int add(int a, int b)
{
	return (a + b);
}	
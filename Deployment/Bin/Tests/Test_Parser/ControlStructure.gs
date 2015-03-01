PREP #include <QtCore/QDebug>
FUNC int main()
	CONTROL for (int i=0; i<100; i++)
		STATE qDebug() << i;
	VAR bool quit = false;
	VAR int n = 0;
	CONTROL while (!quit)
		STATE QThread::msleep(100);
		STATE n += 40;
		STATE quit = n>50000;
	VAR QString username = "DanWatkins"
	CONTROL if (username == "JohnKoehn")
		STATE qDebug() << 56;
	CONTROL elseif (username == ""Noob"" && false)
		CONTROL while (true)
			STATE qDebug() << "Stuck in a loop that will never execute";
	CONTROL else
		STATE qDebug() << "You must be Dan";
PREP #include <QtCore/QDebug>
CLASS class Book
	ENABLE_PUBLIC
	FUNC Book()
		STATE qDebug() << "We made a book";
	FUNC ~Book()
		STATE qDebug() << "We destroyed a book";
	FUNC void setText(const QString & text)
		STATE mText = text;
	FUNC void read()
		STATE qDebug() << mText;
	ENABLE_PRIVATE
	VAR QString mText;
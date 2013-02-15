#ifndef PRODUCER_HPP_
#define PRODUCER_HPP_

#include <QObject>
#include <QStringList>

class Producer: public QObject
{
	Q_OBJECT

public:
    Producer();

public slots:
    void produce();
signals:
    void produced(QString data, int index);
    void finished();

private:
	QStringList m_result;
	QString m_filepath;
	QString m_thumbPng;
	int m_index;

};
#endif /* PRODUCER_HPP_ */

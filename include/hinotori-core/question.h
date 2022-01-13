#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>
#include <QString>

#include "hinotori-core_global.h"

class HINOTORICORE_EXPORT Question : public QObject {
  Q_OBJECT
 public:
  explicit Question(QObject *parent = nullptr);

 private:
  QString message;
  QList<QString> possibleAnswers;
  qsizetype correctAnswerIndex;

 signals:
};

#endif  // QUESTION_H

#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QSpinBox>

class HexSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    HexSpinBox(QWidget *parent = nullptr);
    unsigned int hexValue() const { return u(value()); }
    void setHexValue(unsigned int value) { setValue(i(value)); }
    void setRange(unsigned int max);
    bool fillField() const { return m_fillField; }
    void setFillField(bool fillFieldWidth) { m_fillField = fillFieldWidth; }

protected:
    QString textFromValue(int value) const;
    int valueFromText(const QString &text) const;
    QValidator::State validate(QString &input, int &pos) const;

private:
    unsigned int m_maxRange = UINT_MAX;
    bool m_fillField = true;
    inline unsigned int u(int i) const { return *reinterpret_cast<unsigned int *>(&i); }
    inline int i(unsigned int u) const { return *reinterpret_cast<int *>(&u); }
};

#endif // HEXSPINBOX_H

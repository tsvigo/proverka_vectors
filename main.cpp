#include "dialog.h"

#include <QApplication>

#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QDebug>

//########################################################################################################
class NeuralNetwork {
public:
    QVector<int> neurons;
    QVector<int> synapses;

    void train(int threshold) {
        int sum = 0;
        while (true) {
            sum = 0;
            for (int i = 0; i < neurons.size(); i++) {
                sum += neurons[i] * synapses[i];
            }
            if (sum > threshold) {
                break;
            }
            for (int i = 0; i < synapses.size(); i++) {
                synapses[i] += 1;
            }
        }
        save();
    }

    void save() {
        QFile fileNeurons("neurons.txt");
        QFile fileSynapses("synapses.txt");
        if (fileNeurons.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&fileNeurons);
            for (int i = 0; i < neurons.size(); i++) {
                out << neurons[i] << " ";
            }
            fileNeurons.close();
        }
        if (fileSynapses.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&fileSynapses);
            for (int i = 0; i < synapses.size(); i++) {
                out << synapses[i] << " ";
            }
            fileSynapses.close();
        }
    }

    void load() {
        QFile fileNeurons("neurons.txt");
        QFile fileSynapses("synapses.txt");
        if (fileNeurons.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&fileNeurons);
            QString line = in.readLine();
            neurons.clear();
            foreach (QString str, line.split(" ")) {
                neurons.append(str.toInt());
            }
            fileNeurons.close();
        }
        if (fileSynapses.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&fileSynapses);
            QString line = in.readLine();
            synapses.clear();
            foreach (QString str, line.split(" ")) {
                synapses.append(str.toInt());
            }
            fileSynapses.close();
        }
    }

    int getSum() {
        int sum = 0;
        for (int i = 0; i < neurons.size(); i++) {
            sum += neurons[i] * synapses[i];
        }
        return sum;
    }
};
//########################################################################################################
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    
    NeuralNetwork network;
    network.neurons << 1;
    network.synapses << 1;

    QPushButton button("Train and Save");
    QObject::connect(&button, &QPushButton::clicked, [&network]() {
        network.train(10);
    });

    QPushButton button2("Load and Display");
    QObject::connect(&button2, &QPushButton::clicked, [&network]() {
        network.load();
        qDebug() << "Sum: " << network.getSum();
    });

    button.show();
    button2.show();
    return a.exec();
}

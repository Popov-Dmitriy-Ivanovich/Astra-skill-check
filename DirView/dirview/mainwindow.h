#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QTreeView>
#include <QVBoxLayout>

class MainWindow : public QWidget {
public:
  explicit MainWindow(QWidget *parent = 0) : QWidget(parent) {

    // set current user dirrectory as start dirrectory
    rootPath = QDir::homePath();

    model.setRootPath("");
    model.iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);
    // show hidden files
    model.setFilter(QDir::AllEntries | QDir::Hidden);

    tree = new QTreeView(this);
    tree->setModel(&model);
    if (!rootPath.isEmpty()) {
      const QModelIndex rootIndex = model.index(QDir::cleanPath(rootPath));
      if (rootIndex.isValid())
        tree->setRootIndex(rootIndex);
    }

    // Demonstrating look and feel features
    tree->setAnimated(false);
    tree->setIndentation(20);
    tree->setSortingEnabled(true);
    const QSize availableSize = QApplication::desktop()->availableGeometry(tree).size();
    tree->resize(availableSize / 2);
    tree->setColumnWidth(0, tree->width() / 3);

    searchBar = new QLineEdit(this);

    layout = new QVBoxLayout(this);
    layout->addWidget(searchBar);
    layout->addWidget(tree);

    setMinimumHeight(400);
    setMinimumWidth(750);

    connect(searchBar, &QLineEdit::textEdited, this, &MainWindow::changeModelFilter);
  }

public slots:
  void changeModelFilter(const QString &text) {
    filterList.clear();
    model.setNameFilters(filterList);
    filterList << "*" + text + "*";
    model.setNameFilters(filterList);
    model.setNameFilterDisables(false);
  }

private:
  QString rootPath;
  QFileSystemModel model;
  QTreeView *tree;
  QLineEdit *searchBar;
  QVBoxLayout *layout;
  QStringList filterList;
};

#endif // MAINWINDOW_H

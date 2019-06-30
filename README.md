# 基于Qt5的文本编辑器

[TOC]

## 项目介绍

> 本项目打算设计一个简易文本编辑器，能够实现基本的文本处理工作，同时附带一些高级功能。**我们主要的实现平台在windows操作系统上。**为加强用户体验，我们采用全图形界面设计，方便程序与用户交互。
>

> **配置环境**
>
> 编译器：vs2017 msvc2017 qt5.12
>
> 

#### Qt5.12.3安装

[官网](http://download.qt.io/archive/qt/5.12/5.12.3/)下载qt5.12.3

![1561443108462](C:\Users\丁智\AppData\Roaming\Typora\typora-user-images\1561443108462.png)

选择`qt-opensource-windows-x86-5.12.3.exe`下载（windows系统）。一路安装，一般不会有什么问题。**注意选择编译器的时候选择msvc2017。**

安装成功后，添加环境变量`D:\QT\5.12.3\msvc2017_64\bin` 。

**有个要注意的地方是，qt creator编译一遍生成新的一个文件夹，如果有导入照片之类的东西，要把资源文件放在生成的那个文件夹里面，不能放在.pro在的文件夹里面，不然找不到。**当然使用qt原生函数的时候可以用.qrc（xml写成的小数据库）资源管理器导入需要的文件，在编译时这些资源文件会被自动转换成二进制编码。

如果想使用vs编译qt，那就在vs中点击工具->扩展和更新->联机，搜索qt，下载第一个，如图：

<img src="./img/7.jpg" width="400px" />

下载完成后，重启安装，然后选择状态栏上面的qt vs tools->qt options，点击add，添加你的qt位置如`D:\QT\5.12.3\msvc2017_64`，以便vs编译。

### IDE介绍

####    QT Creator 4.9.0(Community)

![qt](./img/qt.jpg)

**Qt Creator** 是一款跨平台的集成开发环境，特别针对Qt开发者，是QtSDK组成的一部分，可运行于Windows, Linux/X11及Mac OS X等桌面操作系统，允许开发者为多桌面环境及移动设备平台创建应用程序。它包括一个可视化调试工具和集成的 GUI 版面和外形设计师。这个编辑器的功能包括语法高亮度显示和自动完成。在 Windows，默认安装它可以使用 MinGW 或 MSVC。从源代码编译时，也可以使用 cdb。

Qt Creator的**代码编辑器**用于辅助创建，编辑，浏览代码，具有对C++及QML语言完整的表达式检查，代码补全，上下文关联，键入代码时的行间错误即时指示等功能：

- 使用C ++，QML和ECMAscript支持的代码编辑器
- 快速代码导航工具
- 语法突出显示和代码完成
- 您键入时的静态代码检查和样式提示
- 支持源代码重构
- 上下文相关帮助
- 代码折叠
- 括号匹配和括号选择模式

Qt Creator 提供两个集成的可视化编辑器，**Qt Designer** 与 **Qt Quick Designer**。

**调试器**方面，C ++的可视化调试器能够解释许多Qt类的结构，从而增加了提示Qt各种类和对象的能力。另外，Qt Creator以清晰简洁的方式显示GDB的原始信息。

- 中断程序执行。
- 逐行执行程序或按指令执行。
- 设置断点。
- 检查调用堆栈内容以及本地和全局变量。

####    Microsoft Visual Studio 2017

![vs2017](./img/vs2017.jpg)

**Microsoft Visual Studio**（简称**VS**）是微软公司的开发工具包系列产品。VS是一个基本完整的开发工具集，它包括了整个软件生命周期中所需要的大部分工具，如UML工具、代码管控工具等等。

**Visual Studio 2017**是微软于2017年3月8日正式推出的新版本，是迄今为止 最具生产力 的 Visual Studio 版本。

<u>它有以下的一些特性，可以帮助我们在处理大型第三方库（如QT,OpenCV）时有着良好的体验，方便了我们在写这个图形应用程序时，面对大量的函数不知道用法时尴尬的处境。</u>

- **IntelliSense功能**，可以帮助我们在键入函数名时，自动提示这个函数的形参和相应的用法介绍。IntelliSense 随着键入描述 API，并使用自动完成功能以提高速度和精确度。 探索新 API 的速度更快，因为可以通过分类缩小值的范围。 
- **在上下文中导航。**在使用QT这样大型代码库时，进行某个特定函数的查找可能会很困难。 Visual Studio 提供“速览定义”和改进的“定位”功能（方便轻松筛选掉不需要的项，并选择仅查找一种类型的项），有助于更轻松地进行导航，快速定位代码上下文或起始标记。同时，通过解决方案资源管理器中的嵌入式对象浏览方式，可以轻松查看代码的对象结构，并快速搜索解决方案中的文件。
- **CodeLens 功能。**我们可以无需离开代码即可通过 CodeLens 快速了解其调用结构并导航至相关函数。 这可以使得整体结构一目了然，在使用C++这样的OOP语言时，多级继承的类和成员可以方便的检索和查找，极大地方便了我们写代码。
- **查找错误列表中的所有问题。**错误列表可通过“一站式”方式导航并更正解决方案中与代码相关的问题，无论这些问题源自何处，从编译和生成到代码分析全部涵盖在内。使用高级“筛选”专注于问题，导航至该问题并进行修复。在错误上单击“代码链接”或按 F1 键以搜索 Web 内容帮助解决您的问题。

### Complier介绍

####    MSVC 2017

**Microsoft Visual C++2017**（简称Visual C++、MSVC、VC++或VC）是微软公司的C++开发工具，具有集成开发环境，可提供编辑C语言，C++以及C++/CLI等编程语言。VC++集成了便利的除错工具，特别是集成了微软Windows视窗操作系统应用程序接口（Windows API）、三维动画DirectX API，Microsoft .NET框架。目前最新的版本是Microsoft Visual C++ 2017。

Visual C++以拥有语法高亮、IntelliSense（智能提示）以及高级调试功能而著称。比如，它允许我们进行远程调试，单步执行等。**还有允许我们在调试期间重新编译被修改的代码，而不必重新启动正在调试的程序。**其编译及创建预编译头文件（stdafx.h）、最小重建功能及累加链接（link）著称。这些特征明显缩短程序编辑、编译及链接的时间花费，在大型软件项目上尤其显著。

### 库

####    Qt 5.12.3

Qt是一个跨平台的桌面，广泛用于开发GUI程序，这种情况下又被称为部件工具箱。也可用于开发非GUI程序，比如控制台工具和服务器。嵌入式和移动应用程序开发框架。支持的平台包括Linux，OS X，Windows，VxWorks，QNX，Android，iOS，BlackBerry，Sailfish OS等。

Qt本身*不是*一种编程语言。这是一个用C ++编写的框架。预处理器MOC（元对象编译器）用于扩展具有诸如信号和插槽之类特征的C ++语言。在编译之前，MOC解析用Qt-C ++编写的源文件，并从中生成符合标准的C ++源文件。因此，框架本身和使用它的应用程序/库可以通过任何符合标准的C ++编译器（如Clang，GCC，ICC，MinGW和MSVC）进行编译。

Qt的开发始于1990年，由挪威程序员Eirik Chambe-Eng和Haavard Nord开发。他们的公司Trolltech公司出售Qt许可证并提供支持，多年来经历了多次收购。今天，前奇趣科技被命名为Qt公司，是Digia公司的全资子公司。总部位于芬兰。尽管Qt公司是Qt背后的主要驱动力，Qt现在是由一个更大的联盟Qt项目开发的。它由全球许多公司和个人组成，遵循精英管理模式。

## 功能目标

简单文本编辑器的设计是基于Microsoft Visual Studio 2017开发的一款小型的软件，主要的设计是为了满足普通用户对文本文档进行一般的简单操作,通过Qt可视化编程环境，直接生成一个友好的用户操作界面，通过这个窗口，用户可以对文本进行如下的基本操作。

### 文件

① 新建：创建一篇空白文档，从“工具栏”或“文件下拉菜单”中创建

② 打开：打开文本（.txt）文件，从“工具栏”或“文件下拉菜单”中打开；或将文本（.txt）文件拖入程序界面打开或应用程序图标上打开；或右键单击文本文件，在“打开方式”中选择本程序打开

③ 保存：保存文档，从“工具栏”或“文件下拉菜单”中打开

④ 另存为：保存文件副本，在不同位置或以不同文件名保存文档，从“工具栏”或“文件下拉菜单”中另存

### 编辑

① 撤销：撤销前一步所进行的操作，从“编辑下拉菜单”或“右键菜单”中撤销

② 删除：删除当前选定字符（串），从“编辑下拉菜单”或“右键菜单”中删除

③ 剪切：复制并删除选定字符（串），从“编辑下拉菜单”或“右键菜单”中剪切

④ 复制：复制选定字符（串），“编辑下拉菜单”或“右键菜单”中复制

⑤ 粘贴：对粘贴内容进行粘贴，从“编辑下拉菜单”或“右键菜单”中粘贴

⑥ 全选：对文本编辑框中文本全部选定，从“编辑下拉菜单”或“右键菜单”中全

⑦ 查找/替换：输入查找内容（和替换内容），可从光标位置逐个查找（或替换）相应内容，也可一次性全部替换掉相应内容，从“工具栏”或“应用下拉菜单”中执行

### 格式

① 字体设置：设置字体、字形及字的大小，从“工具栏”或“应用下拉菜单    ”中设置字体

② 颜色设置：设置字的颜色

## 基本实现思路

> 文本编辑器软件的实现分为前端和后端两部分，前端程序员负责直接和用户交互的部分，利用**Qt5.12**实现便于用户操作的可视化图形界面，精确地获取并理解用户的需求，调用相关的后端功能；而后端程序员使用**自定义的函数及部分Qt接口**完成对文字的处理部分，设计一个便于使用、功能强大的文字处理函数库接口，供前端调用。

### 文本编辑器工作流程

```flow
st=>start: Start
e=>end
i1=>inputoutput: Load text
i2=>inputoutput: Get user reqiurement
op1=>operation: Call the corresponding function to process the text 
op2=>operation: Show text
cond1=>condition: Exit?
o1=>inputoutput: Save text

st->i1->i2->op1->op2->cond1
cond1(no)->i2
cond1(yes)->o1->e
```


### 前端编写


- 完成主要的软件架构以及业务逻辑

- 设计美观且便于使用的GUI

- 完成载入和保存文本的功能

- 获取用户的操作信息，调用后端编写的功能函数处理文档

其中GUI可利用**Qt**框架自带的**Qt Designer**，该工具能够直观、便捷地设计出美观的GUI，搭配Qt强大的文档查阅工具**Qt Assistant**，相信能够较为简便地设计出简洁优雅的用户图形界面。在本次软件的编写中，前端人员负责主要的软件架构，这是由于前端程序员对整个软件的功能以及业务逻辑更加了解，同时也能使得前端和后端分离，降低编写过程中的合作难度。后端程序员只需关注功能的实现，而前端程序员只要关心界面的设计以及与用户的互动。

### 后端编写

由于Qt自带了字符串存储类`QString`、堆栈类`QStack`，因此我们在实现预期功能时主要采用这些类，并在开发过程中基于这些类进行进一步开发。

与文本处理有关的后端接口函数由负责后端的程序员编写，并为前端程序员的需要进行调用

根据实现功能的要求，负责的后端的人使用Qt编写相对应的文本处理函数，并封装在一个接口文件中。接口文件要求:

- 有充分的注释，包括函数功能、参数说明和用法示例等
- 为了保证代码风格一致，函数名使用大写的驼峰命名法
- 涉及图像输入输出的函数，控制传入参数类型与输出参数类型符合前端开发需求
- 接口文件应只包含相应的函数声明，不包括static函数的声明

### 时间线

| 日期       | 任务                       |
| :--------- | :------------------------- |
| 2019.06.03 | 代码风格讨论及确定         |
| 2019.06.06 | 功能函数接口的确认         |
| 2019.06.08 | 后端代码的编写、调试及测试 |
| 2019.06.13 | 前端代码的编写、调试及测试 |
| 2019.06.16 | 整体代码debug              |
| 2019.06.20 | 规划并完成UI设计           |
| 2019.06.24 | 项目文档                   |

### 注意事项

- 在实现功能函数之前，后端程序员需要和前端程序员有充分的交流，并确认函数的接口原型，避免产生接口冲突的情况

- 采用统一的代码风格，由全组人员讨论后制定，不得擅自更改，如果有分歧则少数服从多数

- 代码要有充分的注释，选择有意义的变量名

- 两位后端程序员要先自行测试自己编写的功能函数，通过后相互交换测试，确认没有Bug后方可交给前端程序员

- 保证按照时间线完成相应任务，不得拖延

## 程序涉及的类的说明

> 我们根据需求封装了edit类、TextEditor类、finddialog等，下面对系统中各个模块进行说明。

### edit类——文本编辑框模块

在`edit.h`中被定义，继承了`QTextEdit`类，主要目的是为了重载控制右键菜单的函数，实现对原先默认右键菜单的修改。（最终由于时间原因我们只屏蔽了原有右键菜单，没有实现新的预期功能）

此外，通过继承`QTextEdit`类，还可以安装事件过滤器，实现对`QTextEdit`类缺省快捷对应动作的重定义。（最终由于时间原因我们未完成此部分）

### TextEditor类——文本编辑器界面框架

在这个类中我们定义了文本编辑器界面框架，实现了其主要的若干功能

### finddlg类——查找功能模块的实现

实现了查找与替换功能

## 系统设计难点及解决

> 在设计过程中，我们遇到了很多困难，但我们最终得到了逐一的解决，下面我们简要展开我们遇到的主要困难和主要解决方法

* Undo栈和Redo栈的设计

  撤销与重做过程目的在于实现一个新的数据结构，用于存储每次文本框中的内容更新时存储当前文本编辑器中的内容，在执行撤销操作时，读取保存的最近一次文本编辑框中的内容并加载到文本框中，并将当下文本编辑器中显示的内容再次保存，以便于下一次执行重做功能时再次恢复之前的文本框中的内容。
  
  为此，我们容易探索出，构建两个堆栈用于保存数据信息的方法符合我们的需求，具体来说，我们需要构建一个UndoStack和一个RedoStack，而在Qt中自带了这样的模板类QStack，因此我们建立两个存储QString类型信息的QStack类变量strUndo、strRedo，用于存储每次改变字符后的当前字符串。此外在测试的过程中，为了修复系统接口与我们自定义的函数接口之间的兼容性问题，我们又定义了几个标记变量，用于标记是否使用了撤销功能、是否进入过某个特殊函数等。具体的细节将在下面的代码部分展开描述。
  
* 字体格式和段落格式

  字体格式和段落格式的设定主要是调用qt控件setFontWeight，setFontItalic等函数来实现，获取光标的选定内容利用QTextCursor类，自己设计函数使得字体格式能应用于光标选中内容。段落格式中由于菜单栏无法设置单选，需要在槽函数中添加代码使得单选实现。

* 剪贴板设计思路

  在TextEditor类中创建一个QString成员变量作为剪贴板，用于存储复制剪切操作中的字符串，在构造函数中将其初始化为空字符串。执行复制和剪切时将选中文本存入变量，粘贴时将原本选中内容删除并插入剪贴板内容。

* 字体格式识别

  对于字体加粗等设定最初只能根据按键的状态判定下一步操作为加粗或还原，无法实现word中对于光标选中内容字体状态的识别并据此更改菜单栏状态的功能。因此另外设计一个函数用于修改菜单栏按键的状态，同时用一个connect函数将光标选中的消息与之关联，从而实现一般文本编辑器中加粗的效果。

* 中文读取与保存

  我们注意到，windows自带的文本编辑器打开txt文件输入汉字后保存，文件编码格式是GB2312，因此在我们的文本编辑器中也采用这一编码格式读取文档。

* 查找与替换的实现

  Qt中文本的存储方式是以QString的方式存储，因此只需要调用QString的indexOf方法，就可以找到相应的下标。在主界面中点击查找后，会新建一个findDlg的实例并将当前的文档中存储的内容传给findDlg类。此后findDlg只需要在这一传来的值中查找就可以了。

  查找需要有三个基本按键（从头查找、下一个、上一个），一个对话框供用户输入查找内容，还有一个用于显示查找结果的对话框。当用户点击从头查找时，程序会从头查找待查找内容，这一点的实现比较简单。

  但是要做到上一个和下一个的功能就不是很容易。我用到了qt中的堆栈容器、`QStack<int>`，新建了一个用于存储当前查找到的内容的位置的堆栈。当点击从头查找或下一个时会把当前查找到的内容的位置压入堆栈，而当点击上一个时会把之前压入堆栈的内容弹出。这样就实现了查找上一个和下一个的功能。

  在查找到内容之后还需要将找到的内容高亮处理，查找是在findDlg类中进行的，而高亮显示是在TextEditor类中实现的。因此需要用到qt信号与槽的机制，每当查找一次，fingDlg就会向TextEditor发送一个消息，包含当前搜索到的字符串的下标位置和字符串长度。

  在点击替换按钮后，fingDlg也会向TextEditor发送一个消息，此消息包含替换后的字符串。在TextEditor收到消息后，只需要用replace方法就可以实现替换QString中的字符串。

* 判断文档是否被保存

  调用系统接口`ui->textEdit->document()->isModified()`就可以判断文档是否已经被保存。

  一个关键的实现细节是，我注意到当我们的撤销和重做功能在程序中被使用时，我们的文档保存标记isModified()会出现错误，系统会认为此时的文档经过了保存，然而事实上这时的文档并没有真的被保存。注意到这个细节后，我们增加了一个bool变量undoIsUsed用于表示是否使用过撤销功能，增加了新的判断逻辑：当使用过撤销功能且Undo栈不为空时，即使`isModified()`指示文件已被保存，我们依然认为文档并没有保存。在增加了这一个修正逻辑后，我们的程序可以正确的判断文档的保存情况。

## 开发需求的代码实现

### 文件新建与打开

```c++
void TextEditor::newFile()
{
   if (maybeSave()) {
       isUntitled = true;
       curFile = tr("未命名.txt");
       setWindowTitle(curFile);
       ui->textEdit->clear();
       ui->textEdit->setVisible(true);
   }
   resetStack();
   strUndo.push(ui->textEdit->toPlainText());
}

```

新建文档时如果没有保存之前的文档会提示是否保存，而其中resetStack**()**函数目的在于实现每次打开文档前的堆栈重置与清空，此外，这个函数将重新恢复undoIsUsed标记为初始值0，代表新的文档尚未使用过撤销功能。strUndo**.**push**(**ui**->**textEdit**->**toPlainText**())**实现了将加载的新的空白文档先压入堆栈，以期在将来重做时恢复到初始状态的目的。

在打开文档时，相关函数如下：

```c++
bool TextEditor::loadFile(const QString &fileName)
{
   //resetStack();
   QFile file(fileName); // 新建QFile对象
   if (!file.open(QFile::ReadOnly | QFile::Text)) {
       QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法读取文件 %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
       return false; // 只读方式打开文件，出错则提示，并返回false
   }
   QTextStream in(&file); // 新建文本流对象
   QApplication::setOverrideCursor(Qt::WaitCursor);
   ui->textEdit->setPlainText(in.readAll());
   resetStack();
   strUndo.push(ui->textEdit->toPlainText());
   QApplication::restoreOverrideCursor();
   // 设置当前文件
   curFile = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(curFile);
      ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
   return true;
}

```

根据上述展示可以看出，程序实现逻辑是首先判断是否可读取文档，若不可读取就报错并返回，若可以读取就正常读取文档并加载，并将光标移动到文档末尾。

### 撤销与重做

撤销与重做过程目的在于实现一个新的数据结构，用于存储每次文本框中的内容更新时存储当前文本编辑器中的内容，在执行撤销操作时，读取保存的最近一次文本编辑框中的内容并加载到文本框中，并将当下文本编辑器中显示的内容再次保存，以便于下一次执行重做功能时再次恢复之前的文本框中的内容。

为此，我们容易探索出，构建两个堆栈用于保存数据信息的方法符合我们的需求，具体来说，我们需要构建一个UndoStack和一个RedoStack，而在Qt中自带了这样的模板类QStack，因此我们建立两个存储QString类型信息的QStack类变量strUndo、strRedo，具体代码实现如下：

```c++
//texteditor.h节选
namespace Ui {
class TextEditor;
}
class TextEditor : public QMainWindow
{
    Q_OBJECT
public:
    QStack<QString> strUndo;
    QStack<QString> strRedo;
    void refreshStack();
    void resetStack();
private slots:
	void on_action_Undo_triggered();
    void on_action_Y_triggered();
    void on_textEdit_textChanged();
private:
    bool isUndo=0;
    bool isRedo=0;
    bool isLoadFile=0;
};
//texteditor.cpp节选
void TextEditor::on_action_Undo_triggered()
{
    isUndo=1;
    if(strUndo.size()>1)
    {
        strRedo.push(strUndo.pop());
        ui->textEdit->setPlainText(strUndo.pop());
        strRedo.push(ui->textEdit->toPlainText());
        ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    }
    isUndo=0;
}
void TextEditor::on_action_Y_triggered()
{
    isRedo=1;
    if(strRedo.size()>1)
    {
        strUndo.push(strRedo.pop());
        ui->textEdit->setPlainText(strRedo.pop());
        strUndo.push(ui->textEdit->toPlainText());
        ui->textEdit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    }
    isRedo=0;
}
void TextEditor::on_textEdit_textChanged()
{
    //文本框更新时更新堆栈
    if((!isUndo)&&(!isRedo)&&(!isLoadFile))
    {
        strUndo.push(ui->textEdit->toPlainText());
    }
}
void TextEditor::resetStack()
//实现每次打开新文件时的重置堆栈
{
    strUndo.clear();
    strRedo.clear();
}

```

此外，为了实现在启动后第一次加载的信息能够被压入strUndo堆栈，也为了实现在打开、新建等过程中将第一次加载的字符串压入堆栈，我们需要重写之前搭建好的其它几个函数如下，以实现压栈过程中的一系列细节：

```c++
//texteditor.cpp节选
TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    // 初始化文件为未保存状态
    isUntitled = true;
    // 初始化文件名为"未命名.txt"
    curFile = tr("未命名.txt");
    // 初始化窗口标题为文件名
    setWindowTitle(curFile);
    strUndo.push(ui->textEdit->toPlainText());
    connect(ui->textEdit,SIGNAL(textChanged(QString)),this,SLOT(on_textEdit_textChanged));
}
bool TextEditor::loadFile(const QString &fileName)
{
   //resetStack();
   QFile file(fileName); // 新建QFile对象
   if (!file.open(QFile::ReadOnly | QFile::Text)) {
       QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法读取文件 %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
       return false; // 只读方式打开文件，出错则提示，并返回false
   }

   QTextStream in(&file); // 新建文本流对象
   QApplication::setOverrideCursor(Qt::WaitCursor);
   // 读取文件的全部文本内容，并添加到编辑器中
   isLoadFile=1;
   resetStack();
   ui->textEdit->setPlainText(in.readAll());
   QApplication::restoreOverrideCursor();

   // 设置当前文件
   curFile = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(curFile);
   //   strRedo.push(ui->textEdit->toPlainText());

      strRedo.push(ui->textEdit->toPlainText());
   return true;
}

```

### 查找与替换

#### 从头查找

```c++
void FindDlg::on_findButton_clicked()
{
    find();
    //emit sendQString(QString::number(lastIndex));
    emit sendIndex(lastIndex, ui->findEdit->text().length());//传递查找到的下标
}

bool FindDlg::find()
{
    //获取当前文本内容
    QString str = nowText;
    //获取当前需要查找的字符串
    QString toBeFound = ui->findEdit->text();
    int index =  str.indexOf(toBeFound);
    if (index == -1)
    {
        ui->resultEdit->setText("没有找到"+toBeFound);
        return false;
    }
    else
    {
        ui->resultEdit->setText(QString::number(index));
        //保存上一次查找结果
        lastIndex = index;
        stk.push(index);
        return true;
    }
}

```

####  查找下一个

```c++
void FindDlg::on_nextButton_clicked()
{
    if (stk.isEmpty())
    {
        find();
        emit sendIndex(lastIndex, ui->findEdit->text().length());//传递查找到的下标
    }
    else
    {
        findNext();
        emit sendIndex(lastIndex, ui->findEdit->text().length());//传递查找到的下标
    }
}

bool FindDlg::findNext()
{
    //获取当前文本内容
    QString str = nowText;
    //获取当前需要查找的字符串
    QString toBeFound = ui->findEdit->text();
    //循环从上一次搜索到的地方开始
    int i = lastIndex;
    //上一次搜到的结果
    for (; i<=str.length(); i++)
    {
       if(lastIndex != str.indexOf(toBeFound, i))
       {
           break;
       }
    }
    int index = str.indexOf(toBeFound, i);
    if (index == -1)
    {
        ui->resultEdit->setText("没有找到"+toBeFound);
        return false;
    }
    else
    {
        ui->resultEdit->setText(QString::number(index));
        lastIndex = index;
        stk.push(index);
        return true;
    }
}
```

查找到最后一个，继续按测试，会显示没有找到测试，但最后一个测试的高亮还在，这是一个小bug目前还没有解决。

此外在查找完之后关闭对话框，高亮仍会显示，这一bug目前也还没有解决

#### 查找上一个

```c++
void FindDlg::on_previousButton_clicked()
{
    findPrevious();
    emit sendIndex(lastIndex, ui->findEdit->text().length());//传递查找到的下标
}

bool FindDlg::findPrevious()
{
    if (!stk.isEmpty())
    {
        stk.pop();
    }
    if (stk.isEmpty())
    {
        ui->resultEdit->setText("已经是第一个");
        return false;
    }
    else
    {
        lastIndex = stk.top();
        ui->resultEdit->setText(QString::number(lastIndex));
        return true;
    }
}

```

目前还有一个小bug，由于是用堆栈的形式实现的查找上一个和下一个，因此在查找下一个之后再从头查找，这样查找上一个的功能就会返回之前的位置，出错。

#### 查找后高亮的实现

```c++
void TextEditor::receiveIndex(int index, int length)
{
    replaceIndex = index;
    replaceLength = length;

    //先把之前的格式清除
    QTextCursor cursor = ui->textEdit->textCursor(); //获取当前光标
    cursor.setPosition(lastIndex);                       //定位到下标index的位置
    cursor.setPosition(lastIndex+lastLength, QTextCursor::KeepAnchor);   //文本选择范围[index,index + length]
    //选中完成
    QTextCharFormat fmt;//定义突出显示
    fmt.setBackground(Qt::white);//定义显示的格式
    cursor.mergeCharFormat(fmt);//显示

    //再显示当前的格式
    //QTextCursor cursor = ui->textEdit->textCursor(); //获取当前光标
    cursor.setPosition(index);                       //定位到下标index的位置
    cursor.setPosition(index+length, QTextCursor::KeepAnchor);   //文本选择范围[index,index + length]
    //选中完成
    //QTextCharFormat fmt;//定义突出显示
    fmt.setBackground(Qt::yellow);//定义显示的格式
    cursor.mergeCharFormat(fmt);//显示

    lastIndex = index;
    lastLength = length;
}

```

#### 替换的实现

```c++
void TextEditor::receiveQString(QString replaceStr)
{
    ui->textEdit->setPlainText(((ui->textEdit->toPlainText()).replace(replaceIndex, replaceLength, replaceStr)));
}

```

### 保存与另存为

```c++
bool TextEditor::save()
{
   if (isUntitled) {
       return saveAs();
   } else {
       return saveFile(curFile);
   }
}
bool TextEditor::saveFile(const QString &fileName)
{
   QFile file(fileName);

   if (!file.open(QFile::WriteOnly | QFile::Text)) {

       // %1和%2分别对应后面arg两个参数，/n起换行的作用
       QMessageBox::warning(this, tr("多文档编辑器"),
                   tr("无法写入文件 %1：/n %2")
                  .arg(fileName).arg(file.errorString()));
       return false;
   }
   QTextStream out(&file);
   // 鼠标指针变为等待状态
   QApplication::setOverrideCursor(Qt::WaitCursor);
   out << ui->textEdit->toPlainText();
   // 鼠标指针恢复原来的状态
   QApplication::restoreOverrideCursor();
   isUntitled = false;
   // 获得文件的标准路径
   curFile = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(curFile);
   return true;
}
bool TextEditor::saveAs()
{
   QString fileName = QFileDialog::getSaveFileName(this,
                                         tr("另存为"),curFile);
   if (fileName.isEmpty()) return false;
   return saveFile(fileName);
}


```

### TextEdit类的继承

为了实现重写系统自带右键菜单与屏蔽系统自带快捷键的目的，我们继承了TextEdit类，其中文本编辑框的右键菜单是一个QTextEdit类中的函数contextMenuEvent，为了重写这个函数，我们需要继承这个类，并在继承类中重载这个函数。此外，在默认的文本编辑框中自带了Ctrl+Z、Ctrl+Y等快捷键，这些快捷键会指向系统自带的接口而非我们定义的Undo/Redo函数，为了屏蔽系统自带的快捷键，我们同样需要继承QTextEdit类并在派生类中通过installEventFilter安装事件过滤器，从而过滤掉原先QTextEdit类中默认的快捷键事件。

为了实现对右键菜单的重写，我们新建了edit类，下面是其头文件和cpp文件的实例代码（由于时间有限，我们最终没有完成这部分工作，因而以下代码仅为展示实现这样功能需要的大致代码框架，这代表了我们继承类来解决问题的思想，但我们最终由于时间原因未能完成这部分工作）。

```c++
//edit.h节选
#ifndef EDIT_H
#define EDIT_H

#include <QTextEdit>

class Edit : public QTextEdit
{
    Q_OBJECT
public:
    explicit Edit(QWidget *parent = nullptr);

signals:

public slots:

protected:
    void contextMenuEvent(QContextMenuEvent* e);
};

#endif // EDIT_H

//edit.cpp节选
#include "edit.h"
#include <QMenu>
#include<QContextMenuEvent>
#include "texteditor.h"
Edit::Edit(QWidget *parent) : QTextEdit(parent)
{

}
void Edit::contextMenuEvent(QContextMenuEvent *e)
//重定义右键菜单
{
    QMenu* menu = new QMenu;
    QAction* undo =menu->addAction("撤销",this,SLOT(Undo()));
    undo->setEnabled(document()->isUndoAvailable());
    menu->exec(e->globalPos());
    delete menu;
}

```

### 全选的实现

```c++
//texteditor.h节选
namespace Ui {
class TextEditor;
}
class TextEditor : public QMainWindow
{
    Q_OBJECT
private slots:
    void on_action_selectAll_triggered();
};
//texteditor.cpp节选
void TextEditor::on_action_selectAll_triggered()
{
    ui->textEdit->selectAll();
}

```

### 字体设置

```c++
void TextEditor:: mergeformat(const QTextCharFormat &fmt)
{
/*设置光标的选区，使格式作用于选区内的字符，若没有选区则作用于光标所在处的字符*/
    QTextCursor cursor =ui->textEdit->textCursor();
    if ( !cursor.hasSelection() )
           cursor.select( QTextCursor::WordUnderCursor );
    cursor.mergeCharFormat( fmt );

    ui->textEdit->mergeCurrentCharFormat( fmt );

}
void TextEditor::textBold()//加粗
{
    QTextCharFormat fmt;
    fmt.setFontWeight( ui->action_Bold->isChecked() ? QFont::Bold : QFont::Normal );//根据按键状态判断加粗或还原
    mergeformat( fmt );
}

void TextEditor::textItalic()//倾斜
{
    QTextCharFormat fmt;
//根据按键状态判断倾斜或还原
    fmt.setFontItalic( ui->action_Italic->isChecked() );
    mergeformat( fmt );
}

void TextEditor::textUnderline()//下划线
{
    QTextCharFormat fmt;
//根据按键状态判断下划线或还原
    fmt.setFontUnderline( ui->action_Underline->isChecked() );
    mergeformat( fmt );
}
void TextEditor::textCurrentFormatChanged(const QTextCharFormat &fmt)
{// 当光标所在处字符格式有变化，工具栏做出相应改变
    ui->action_Bold->setChecked( fmt.font().bold() );
    ui->action_Italic->setChecked( fmt.fontItalic() );
    ui->action_Underline->setChecked( fmt.fontUnderline() );
}
TextEditor::TextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextEditor)
{
//在构造函数中增加connect函数使得选中的字体格式变化时能够调用上述函数
    connect(ui->textEdit, &QTextEdit::currentCharFormatChanged, this, &TextEditor::textCurrentFormatChanged);
}

```

### 段落格式排版

```c++
void TextEditor::on_action_Left_triggered()
{//左对齐
    ui->textEdit->setAlignment( Qt::AlignLeft );
    if(ui->action_Left->isChecked())//设置成单选
    {
            ui->action_Right->setChecked(false);
            ui->action_Center->setChecked(false);
    }
     else ui->action_Left->setChecked(true);
}

void TextEditor::on_action_Right_triggered()
{//右对齐
    ui->textEdit->setAlignment( Qt::AlignRight );
    if(ui->action_Right->isChecked())//设置成单选
    {
            ui->action_Left->setChecked(false);
            ui->action_Center->setChecked(false);
            ui->action_Just->setChecked(false);
    }
    else ui->action_Right->setChecked(true);
}

void TextEditor::on_action_Center_triggered()
{//居中
    ui->textEdit->setAlignment( Qt::AlignCenter );
    if(ui->action_Center->isChecked())//设置成单选
    {
            ui->action_Just->setChecked(false);
            ui->action_Right->setChecked(false);
            ui->action_Left->setChecked(false);
    }
    else ui->action_Center->setChecked(true);
}
void TextEditor::on_action_Just_triggered()
{//两端对齐
    ui->textEdit->setAlignment( Qt::AlignJustify );
    if(ui->action_Center->isChecked())//设置成单选
    {
            ui->action_Center->setChecked(false);
            ui->action_Right->setChecked(false);
            ui->action_Left->setChecked(false);
    }
    else ui->action_Just->setChecked(true);
}

```

### 具体字体和颜色

```c++
#include <QColorDialog>
#include <QFontDialog>
void TextEditor::textColor()
{
    QColor c =QColorDialog::getColor(Qt::red, this );//调用颜色对话框
    if ( c.isValid() )
    {
         QTextCharFormat fmt;
         fmt.setForeground( c );
         mergeformat( fmt );
    }
}

void TextEditor::textFont()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok);//调用字体对话框
    if(ok){
        QTextCharFormat fmt;
        fmt.setFont(f );
        mergeformat( fmt );
    }
}
c
```

### 剪贴板的实现

构造一个QString成员变量用于存储选中的字符串信息，实现剪贴板功能，但是缺点在于无法存储字体信息

```c++
void TextEditor::textCopy()
{
    /*设置光标的选区，
    将选中的字符存入剪贴板*/
    pasteBoard="";
    QTextCursor cursor =ui->textEdit->textCursor();
    pasteBoard=cursor.selectedText();
}

void TextEditor::textCut()
{
    /*设置光标的选区，
    将选中的字符存入剪贴板，同时删除选中内容*/
    QTextCursor cursor =ui->textEdit->textCursor();
    pasteBoard=cursor.selectedText();
    cursor.removeSelectedText();
}

void TextEditor::textPaste()
{
    /*删除当前选中内容，插入剪贴板文本*/
    QTextCursor cursor =ui->textEdit->textCursor();
    cursor.removeSelectedText();
    cursor.insertText(pasteBoard);
}

```



## 测试报告

* 在查找结束后的高亮，也会被计入Undo与Redo堆栈导致撤销出现错误，我们认为可以引入新的变量和函数来记录这一变化，进而解决这一问题，但由于时间原因，没能实现这一部分功能；

* 在对字体进行格式设置后，系统会认为文本内容发生了变化，进而将文本错误的压入堆栈，导致了后续撤销出现错误，我认为同样可以通过引入新的变量记录这一变化过程来解决，但由于时间原因，我们没能实现这个功能；

* 由于字体设置后文本被保存成了txt格式，因而文本中的字体格式信息会丢失，我们没有找到用txt格式保存字体的合理方式（或许用类似markdown的标记方式可以储存字体格式，但我们认为功能过于复杂，可能并不好实现，需要借助现成的第三方库实现markdown类似功能）。

* 按下Ctrl+Z和Ctrl+Y后，系统会调用自带的撤销与重做接口而不会使用我们定义的借口，通过在继承出来的edit类中加入事件过滤器可以解决此问题，但由于时间原因，我们没有完成此功能。
* 查找和替换中，由于是用堆栈的形式实现的查找上一个和下一个，因此在查找下一个之后再从头查找，这样查找上一个的功能就会返回之前的位置，出错。
* 查找和替换中，查找到最后一个，继续查找，会显示没有找到字符，但最后一个字符试的高亮还在，这是一个小bug目前还没有解决。此外在查找完之后关闭对话框，高亮仍会显示，这一bug目前也还没有解决，但我们提出了引入新变量记录这个变化，并在结束查找后根据记录恢复初始状态的方法解决，但由于时间原因未实现。

## 人员职责

| 角色 | 姓名（学号）         | 职责                                                         |
| ---- | -------------------- | ------------------------------------------------------------ |
| 组长 | 丁智（3170104656）   | 统筹项目、撰写项目报告、设计UI与前端框架、实现后端查找与替换的部分功能、实现打开与新建文本的部分功能、实现撤销与重做的数据接口、测试项目与debug、TextEdit类的继承框架、录制视频等 |
| 组员 | 潘盛琪（3170105737） | 设计UI与前端框架、实现后端查找与替换的部分功能、实现打开与新建文本的部分功能、实现保存与另存为、测试项目与debug等 |
| 组员 | 王亦（3170102363）   | 实现字体设置与格式设置功能、实现了查找与替换部分功能、实现了剪贴板功能、实现了查找与替换部分功能、测试项目与debug等 |

## 程序使用说明

### 文件

① 新建：创建一篇空白文档，从“工具栏”或“文件下拉菜单”中创建

② 打开：打开文本（.txt）文件，从“工具栏”或“文件下拉菜单”中打开；或将文本（.txt）文件拖入程序界面打开或应用程序图标上打开；或右键单击文本文件，在“打开方式”中选择本程序打开

③ 保存：保存文档，从“工具栏”或“文件下拉菜单”中打开

④ 另存为：保存文件副本，在不同位置或以不同文件名保存文档，从“工具栏”或“文件下拉菜单”中另存

### 编辑

① 撤销：撤销前一步所进行的操作，从“编辑下拉菜单”中撤销

② 重做：重做前一步所撤销的操作，从“编辑下拉菜单”中撤销

③ 剪切：复制并删除选定字符（串），从“编辑下拉菜单”中剪切

④ 复制：复制选定字符（串），“编辑下拉菜单”中复制

⑤ 粘贴：对粘贴内容进行粘贴，从“编辑下拉菜单”中粘贴

⑥ 全选：对文本编辑框中文本全部选定，从“编辑下拉菜单”中全选

⑦ 查找/替换：输入查找内容（和替换内容），可从光标位置逐个查找（或替换）相应内容，也可一次性全部替换掉相应内容，从“工具栏”或“应用下拉菜单”中执行

### 格式

① 字体设置：设置字体、字形及字的大小，从“工具栏”或“应用下拉菜单    ”中设置字体

② 颜色设置：设置字的颜色

③ 段落设置：设置段落格式

### <font color=Red>注意事项</font>

* <font color=Red>由于程序编写中存在不足，我们尚未屏蔽文本框控件的缺省快捷键。因而对快捷键的调用会调用系统默认接口而非我们定义的接口，故为了正常使用我们的程序，请不要随意使用在其它文本编辑器中常用的快捷键，例如：请不要在程序中使用Ctrl+Z的方式调用撤销功能，而应直接在工具栏中调用撤销功能；请不要在程序中使用Ctrl+Y的方式调用重做功能，而应直接在工具栏中调用重做功能。但并非基于文本框控件的快捷键是可以被正常调用的，例如Crtl+F快捷键可以正常调用我们定义的查找功能，因而可以正常使用。</font>

## 总结

经过了连续数日的不懈努力，我们终于完整的完成了面向对象程序设计《基于Qt5简易文本编辑器》的课程设计。在做此实验中虽然碰到了很多困难，但是在克服困难的同时我们获益良多。

通过这次课程设计，我们巩固了C++语言知识，培养了分析问题与解决问题的能力，也更好的整理了自己变成的思路，将课本中的知识与实际项目问题更好的结合在了一起。

这次课程设计，也进一步提高了我们对编程的喜爱。通过Windows编程，设计出了和谐的美妙的可视化界面，实现了很多功能。更让我回味无穷的是那编程的过程，虽然遇到了很多问题，但通过上网查阅资料，与同学交流等，最后一一解决了，真的很是享受。也从中学到了很多新的东西，其中既有程序方面的有关新的知识，也有一些关于做人的道理。一个人的力量永远是有限的，但两个人，三个人以上的力量永远是无限的。学会团队合作，把自己知道的东西学会分享给同学，在分享的过程中，你既收获到了喜悦，也将获得新的知识。方法永远比困难多，不应该看到问题难了，就没有信息去面对，只要有一颗火热的心，所有的问题都不是问题。
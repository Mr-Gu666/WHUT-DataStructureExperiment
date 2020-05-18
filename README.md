# WHUT-DataStructureExperiment
武汉理工大学数据结构实验

<h2>
    <ul>
        <li><a id="Huffman">哈夫曼树</a></li>
    </ul>
</h2>

<h2>
    <a href="#Huffman">哈夫曼树</a>
</h2>

<h4>
    <b>0.重点</b>
</h4>

![image-20200518150131304](C:\Users\70965\AppData\Roaming\Typora\typora-user-images\image-20200518150131304.png)

这是文件的存储方式。

byte范围：0-255

char范围：-128-127

unsigned char范围: 0-255

数据存储是二进制的，都是010101010这种。

这种必然可以当作数字来看，所以可进行如下操作：

1.从文件读取字节，转换为int值，统计某字节出现几次

   因为字节是8位，2^8=256，所以用int表示byte绰绰有余，且weight[]数组大小256就OK了

2.将哈夫曼编码合并再分为8个字符一组，计算8位二进制的十进制数字，将其转换为unsigned char写入文件

   用unsigned char是因为它和byte范围相同

<h4>    
    <b>1.打开文件读取数据</b>
</h4>

用c++的<fstream>进行文件读写

```C++
#include <fstream>

//打开文件
ifstream in;
//ios::in-从文件读取
//ios::binary-二进制打开
in.open(fileName,ios::in|ios::binary);

//关闭文件
in.close();
```

读取文件数据

```c++
int ch = -1;
while((ch=in.get())!=EOF)
{
	++weight[ch];
}
```

<h4>
    <b>2.构造哈夫曼树</b>
</h4>

这个不难，可以直接看代码

<h4>
    <b>3.构造哈夫曼编码</b>
</h4>

用bfs()直接递归出来就可以了

<h4>
    <b>4.将哈夫曼编码分为8个一组准备转换为byte</b>
</h4>

这里需要注意两点：

（1）substr()的使用：

​		  substr(a,b)--从a开始，取b位

（2）后续不满8位，要补0

<h4>
    <b>5.将分好的编码转换为byte(unsigned char)</b>
</h4>

计算8位的二进制编码（虽然是字符串形式）表示的数字，并用unsigned char存储该数字

<h4>
    <b>6.写入文件，计算大小</b>
</h4>

“写入文件”代码里面有，想强调计算文件大小。

FOCUS！

一定要重新打开文件再计算大小。

写入的.huf文件我不知道直接计算大小会不会出错，但是读取原文件之后，未关闭直接计算大小，数据是不对的。

```c++
outFile.open(newFileName, ios::in | ios::binary);
//将文件指针指向末尾
outFile.seekg(0, ios::end);
//单位为byte
size_t afterNum = outFile.tellg();
outFile.close();
```

<h4>
    <b>题外：</b>
</h4>

我为了测试string转换为byte时是否正确，进行了解压缩。

解压缩的代码要注意 00011010 这种有前置0的数据，为防止这种数据出现错误，要计算解压缩出来的编码有没有8位，不足8位，在编码前面要添加“0”
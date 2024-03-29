# Practical-course-project
本项目库中的项目为个人项目，git账户名称：sunshile18 <br>
项目库地址为https://github.com/sunshile18/Practical-course-project  <br>
项目完成人：边煦琼 201900460009 信安班 <br>
在本项目库中，除了实现的代码cpp文件（内含程序代码注释和说明）外，还有一些项目报告的pdf文档（大多为说明文档，内含程序代码说明和运行结果截图）和PNG图片文件（大多为程序运行结果截图）。<br>
但是在本网站中或许不能直接像阅读代码一样阅读pdf文档和PNG图片。<br>
我发现一个方法，可以点击绿色的“Code”按钮中，再点击“Download ZIP”,然后就可以下载所有的文件（包括代码cpp文件、pdf文档和png图片）到本地上，即可通过本地的阅读器进行阅读。<br><br>

# 已完成的项目
## 1.SM3生日攻击
## 2.SM3之Rho攻击
## 3.SM3之长度扩展攻击
运行指导：对于以上三个项目我都已提交了项目代码的cpp文件，可以在vs中创建新文件后，将cpp文件加入到源文件中即可运行。<br>
项目说明与运行结果：以上三个项目的说明在“SM3报告(含算法流程、生日攻击、Rho攻击和长度扩展攻击).pdf”中已经写明，包括实现思路、代码说明、运行结果等。<br>
## 4.Merkle树的实现（初步实现+改进实现）和 Merkle树的存在与不存在证明
运行指导：对于以上项目我都已提交了项目代码的cpp文件，可以在vs中创建新文件后，将cpp文件加入到源文件中即可运行。<br>
项目说明与运行结果：以上项目的说明在“Merkle树实现与证明.pdf”中已经写明，包括实现思路、代码说明、运行结果等。<br>
## 5.ECDSA的签名伪造
运行指导：对于以上项目我已提交了项目代码的cpp文件，可以在vs中创建新文件后，将cpp文件加入到源文件中即可运行。但是我在网上并没有找到中本聪的公钥以及具体所选择的椭圆曲线参数，所以在cpp文件中没有main，在运行时，可以将以下main函数的代码加入，根据运行中的提示把被伪造的中本聪的公钥与参数输入，并把所选的椭圆曲线参数进行初始化，即可进行运行。<br>
项目说明：ECDSA的签名伪造的具体说明与推导在“ECDSA签名伪造推导.pdf”中已经写明。<br>
代码具体运行与指导可以在三个png文件中查看，包括“椭圆曲线参数初始化.png”,"ECDSA签名伪造之main函数.png","ECDSA签名伪造运行.png"。<br>
代码说明：由于代码中有随机数的u,v的引入，所以在运行时有时会出现除0的错误，导致运行失败，当各参数选取适当时，可以运行通过。<br>
## 6.ECDSA从签名推出公钥
项目文件：“ECDSA从签名推出公钥.pdf”<br>
项目说明：课堂上老师讲述了SM2中从签名推出公钥的技巧，并在项目中要求对于此技巧应用在ECDSA中，并给出报告，因此从签名推出公钥在ECDSA中的应用在此报告中进行了详细的说明。<br>
## 7.签名算法中存在的隐患与攻击（verify the above pitfalls）
项目文件：“签名算法中存在的隐患与攻击.pdf”<br>
项目说明：课堂上老师简单总结了签名算法中存在的隐患与攻击，而在此报告中详细地说明了几大常见的攻击在SM2和ECDSA两个算法中的具体应用与数学推导，并进行了概念化的证明。<br>
## 8.ECMH实现
运行指导：对于以上项目我已提交了项目代码的cpp文件，可以在vs中创建新文件后，将cpp文件加入到源文件中即可运行。在运行前，需要将以下调用目标函数的main函数的代码加入，并把所选的椭圆曲线参数进行初始化，即可进行运行。<br>
项目说明：在本项目中是求集合的HASH值，可以将集合中的元素映射到椭圆曲线上，然后由于若所选的椭圆曲线为阿贝尔群,则在椭圆曲线上的加法操作有如下性质:a+b=b+a。因此可以使得以任何顺序求出的集合值不变（只要集合的元素不变）<br>
代码具体运行与指导可以在三个png文件中查看，包括“椭圆曲线参数初始化.png”,"ECMH之main函数.png","ECMH之运行结果.png"。<br>
## 9.SM2实现
项目说明：在此项目中包括了SM2的加解密函数的实现和SM2的签名与验签算法的实现，包括文件“SM2加解密算法.cpp”与“SM2签名验证算法.cpp”。<br>
运行指导：对于以上项目我已提交了项目代码的cpp文件，可以在vs中创建新文件后，将cpp文件加入到源文件中即可运行。在运行前，需要在main函数中将调用的目标函数的代码加入，并把所选的椭圆曲线参数进行初始化，即可进行运行。国密推荐椭圆曲线参数为：p=FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF，a=FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC，b=28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93，                            n= FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123，Gx=32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7，Gy=BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0，h=00000001。也可以自行设置所选的椭圆曲线参数，所以在运行前需要将参数进行初始化。<br>
## 10.SM2_PGP
运行指导：对于以上项目我已提交了项目代码的cpp文件，可以在vs中创建新文件后，将cpp文件加入到源文件中即可运行。在运行前，需要将以下调用目标函数的main函数的代码加入，并把所选的椭圆曲线参数进行初始化，即可进行运行。<br>
项目说明：在PGP加密算法中，首先随机生成会话密钥，然后使用对方（接收方）的公钥对于会话密钥进行加密得到密文1，然后再用会话密钥对于消息进行对称加密，得到密文2，然后将密文1和密文2都给接收方。在PGP解密算法中，当接受方收到两个密文后，首先用自己的私钥对于密文1进行解密，得到会话密钥，再用会话密钥对于密文2进行解密，得到明文消息。<br>
## 11.SM2_两方签名
项目说明：此项目我一共提交了三个cpp，分别是“SM2_两方签名函数模块实现.cpp”,“SM2_两方签名网络交互（TCP_A）.cpp”和“SM2_两方签名网络交互（TCP_B）.cpp”。<br>
其中，“SM2_两方签名函数模块实现.cpp”实现了两方签名算法中所用到的各个步骤的分步函数模块，但是还未进行通信。<br>
而在“SM2_两方签名网络交互（TCP_A）.cpp”和“SM2_两方签名网络交互（TCP_B）.cpp”中，对于两方交互的过程进行了编程，在这里使用了TCP进行通信，因此将两方函数的返回值等通过TCP进行交互传递，在这里没有使用加密通信，如果必要的话可以使用TLS\SSL进行更加安全的通信。<br>
运行指导：对于以上项目我已提交了项目代码的cpp文件，可以在vs中创建新文件后，将cpp文件加入到源文件中即可运行。在运行前，需要将所选的椭圆曲线参数进行初始化，即可进行运行。<br><br>
## 12.SM3优化
项目说明：此项目中我主要对于SM3算法进行了优化，优化的方法主要为循环展开，见文件“SM3优化.cpp”。除此之外，我还对于SIMD指令进行了了解和简单地使用，主要将此优化方法应用在了更加直接和简单的矩阵乘的优化中，而没有来得及将其应用于SM3中进行优化，见文件“矩阵乘SIMD加速.cpp”。<br>
运行指导：对于以上项目我已经提交了项目代码的cpp文件，可以在vs中创建新文件后，将cpp文件加入到源文件中即可运行。<br>
代码说明具体可见CPP文件注释，而程序运行结果可见文件“SM3优化运行结果.png”。<br>
## 13.SM4加速
项目说明：此项目中我主要对于SM4算法进行了优化，优化的方法主要为循环展开，见文件“SM4加速.cpp”。<br>
运行指导：对于以上项目我已经提交了项目代码的cpp文件，可以在vs中创建新文件后，将cpp文件加入到源文件中即可运行。<br>
代码说明具体可见CPP文件注释，而程序运行结果可见文件“SM4加速运行结果.png”。<br><br>




# 未完成的项目
## 1.MPT
## 2.分析比特币区块的每一个比特
## 3.SM2两方加密
## 4.Google Password Checkup
## 5.Find a key with hash value "sdu_cst_20220610" under a message composed of your name followed by your student ID.
## 6.Find a 64-byte message under some k fulfilling that their hash value is symmetrical

# 参考文献
https://blog.csdn.net/wcc19840827/article/details/103857971?spm=1001.2101.3001.6650.18&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-18-103857971-blog-81489915.pc_relevant_downloadblacklistv1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-18-103857971-blog-81489915.pc_relevant_downloadblacklistv1&utm_relevant_index=23 <br><br>
https://copyfuture.com/blogs-details/20210623061641500Z <br><br>
https://blockchain-fans.blog.csdn.net/article/details/85339243?spm=1001.2101.3001.6650.12&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-12-85339243-blog-81135439.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Edefault-12-85339243-blog-81135439.pc_relevant_default&utm_relevant_index=20 <br><br>
https://blog.csdn.net/qq_40662424/article/details/121637732 <br><br>
https://blog.csdn.net/kawayiyy123/article/details/106857256/ <br><br>
https://blog.csdn.net/qq_35699583/article/details/113060927?spm=1001.2101.3001.6650.2&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-2-113060927-blog-121555000.pc_relevant_multi_platform_featuressortv2dupreplace&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-2-113060927-blog-121555000.pc_relevant_multi_platform_featuressortv2dupreplace&utm_relevant_index=5 <br><br>
https://blog.csdn.net/hacker_lpy/article/details/124211114 <br><br>

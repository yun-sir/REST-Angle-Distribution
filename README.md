# REST-Angle-Distribution
pandaX中蒙卡模拟软件REST中的粒子发射方向验证及探求
其中geometry.gdml为几何结构基本文件，几何结构主要设置为一个球壳，c1为其输出结构图；
TEST_AD_G4.rml为主要的G4模拟文件
test_ad.C为解析restRoot文件脚本
generator_Angle_Distribution.C为产生的角分布脚本
结果存在各文件夹中flux=单方向，iso=各向同性，cos_theta=cosTheta分布，0.0-0.1为对角分布TH1D文件设置为0.0-0.1 rad的均匀分布。

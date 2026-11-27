import os


# os.system("python reg.py > a")
# os.system("python ref_reg.pyc > b")
# os.system("diff a b")

# os.system("python reg.py -d COS > a")
# os.system("python ref_reg.pyc -d COS > b")
# os.system("diff a b")


# os.system("python reg.py -n 333 > a")
# os.system("python ref_reg.pyc -n 333 > b")
# os.system("diff a b")

# os.system("python reg.py -n b > a")
# os.system("python ref_reg.pyc -n b > b")
# os.system("diff a b")



os.system("python reg.py -a Qr > a")
os.system("python ref_reg.pyc -a Qr > b")
os.system("diff a b")

os.system("python reg.py -t intro > a")
os.system("python ref_reg.pyc -t intro > b")
os.system("diff a b")


os.system("python reg.py -t science > a")
os.system("python ref_reg.pyc -t science > b")
os.system("diff a b")


os.system("python reg.py -t C_S > a")
os.system("python ref_reg.pyc -t C_S > b")
os.system("diff a b")

os.system("python reg.py -t c%S > a")
os.system("python ref_reg.pyc -t c%S > b")
os.system("diff a b")

os.system("python reg.py -d cos -n 3 > a")
os.system("python ref_reg.pyc -d cos -n 3 > b")
os.system("diff a b")

os.system("python reg.py -d cos -a qr -n 2 -t intro > a")
os.system("python ref_reg.pyc -d cos -a qr -n 2 -t intro > b")
os.system("diff a b")

os.system("python reg.py -t=-c  > a")
os.system("python ref_reg.pyc -t=-c  > b")
os.system("diff a b")
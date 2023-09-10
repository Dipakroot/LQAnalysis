import subprocess

def getNEvents_DAS(sample):
    std_output, std_error = subprocess.Popen("dasgoclient --query='summary dataset=%s' | cut -d ':' -f 4 | cut -d ',' -f 1"%sample,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE).communicate()
    names = std_output.replace('\n',' ')
    if names=='':
        print ("PROBLEM")
        print (sample)
        print ()
    return names

def getParent_DAS(sample):
    std_output, std_error = subprocess.Popen("dasgoclient --query='parent dataset=%s'"%sample,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE).communicate()
    names = std_output.replace('\n',' ')
    if names=='':
        print ("PROBLEM")
        print (sample)
        print ()
    return names

def getFileList_DAS(sample):
    std_output, std_error = subprocess.Popen("dasgoclient --query='file dataset=%s status=*'"%sample,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE).communicate()
    names = std_output.decode("ascii").replace('\n',' ')
    if names=='':
        print ("PROBLEM")
        print (sample)
        print ()
    return names

def getXS_DAS(sample):
    std_output, std_error = subprocess.Popen("cmsRun ana.py inputFiles=\"file:root://cms-xrd-global.cern.ch//%s\" maxEvents=-1 2>&1 | grep \"After filter: final cross section\""%sample,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE).communicate()
    names = std_output.replace('\n',' ')
    if names=='':
        print ("PROBLEM")
        print (sample)
        print ()
    return names

inputfile = open("sample_2016_petit.txt", "r")

for line in inputfile:
    sample = line.replace('\n',' ')
    print(sample)
    parent = getParent_DAS(sample)
    nevent = getNEvents_DAS(parent)
    filelist = getFileList_DAS(parent).split()[0]
    xs = getXS_DAS(filelist)
    print("%100s\t : %s : %s"%(parent,filelist,xs))
# with open("sample_2016.txt", "r") as f:
#     contents = f.read()
#     print(contents)

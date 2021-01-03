# Copy this conf.py.example to conf.py and configure all the variables
# beginning with my_, then you will be able run the various test scripts
my_machine_name  = 'YXQUAN'  # short name to identify encodes made on this machine
my_machine_desc  = 'i7 16GB'  # description of hardware, CPU(s), memory, etc
my_sequences     = r'D:\WorkTmp\vvdec-yxquan\ext\all'
my_vvdec_source  = r'D:\WorkTmp\vvdec-CM001' # location of CMakeLists.txt
my_vvdec_decoder = r'D:\WorkTmp\vvdec-CM001\bin\release-static'
my_progress      = True # do you want to see build / encode status on console?
my_adb_cmd       = r'C:\Microsoft\platform-tools\adb.exe'
my_adb_sequences = r'/data/local/tmp/testSeq'
my_adb_decoder   = r'/data/local/tmp/vvdecapp'
my_adb_tmpfolder = r'/data/local/tmp/tmp'
my_make_flags    = ''
# decoder binary name, default vvdecapp
decoder_binary_name = 'vvdecapp'
decoder_library_name = 'vvdec'
version_control = 'git'

# full path of msys shell (ex: r'R:\MinGW\msys\bin\sh.exe')
my_shellpath = ''

# Allow the scripts to use a locally modified output-changing-commits.txt 
# (skipping the download step). Leave False unless you are testing
# commits you intend to push directly after testing (and this is only
# possible if *you* have push rights).
my_local_changers = False

# note that on POSIX systems you can use '~/' to signify your home dir

# location for encoder intermediates. One temp folder will be created
# per run, but should be deleted upon completion, so it does not require
# much space but it should have good throughput. If not defined Python
# will use the default temp folder for your platform and user account
my_tempfolder   = r'D:\WorkTmp\tmp'


# if you want the script to create pastebins of warnings and errors you
# must register at pastebin.com, sign in, then go to http://pastebin.com/api
# to find 'Your Unique Developer API Key'
my_pastebin_key = ''

my_make_flags   = [] # example: ['-j', '4'] for 4-core build parallelism

# add one entry here per build target that you would like to build and test
my_builds = {
    # Examples:
    #
    #'gcc'   :                   # build label (short name)
    #         ('default/',       # unique build folder
    #          'gcc',            # build group, see below
    #          'Unix Makefiles', # cmake generator
    #          'static checked', # short-hand cmake options (see below)
    #          {}),              # env-vars and other keyword arguments
    #
    #'gcc32' : ('gcc32/', 'gcc32', 'Unix Makefiles', 'static', {'CFLAGS':'-m32'}),
    #'llvm'  : ('llvm/', 'gcc', 'Unix Makefiles', 'checked',
    #           {'CC' : 'clang', 'CXX' : 'clang++'}),
    #'vc15'  : ('vc15/', 'vc', 'Visual Studio 15 2017 Win64', 'checked', {}),
    #'vc16'  : ('vc16/', 'vc', 'Visual Studio 16 2019', 'win-arm64', {}),
    #'vc15D' : ('vc15D/', 'vc', 'Visual Studio 15 2017 Win64', 'debug crt noasm ppa', {}),
    #'win32' : ('vc15x86/', 'vc', 'Visual Studio 15 2017', 'static ppa', {}),
    #'mingw' : ('mingw/', 'gcc', 'MinGW Makefiles', 'tests',
    #           {'PATH' : r'C:\mingw64\bin'}),
    #'gcc' : ('default/', 'gcc', 'Unix Makefiles', 'ffmpeg-static', 
    #           {'LD_LIBRARY_PATH' : r'/home/project/lib', 'PKG_CONFIG_PATH' : r'/home/project/lib/pkgconfig'})
    'ndk'  : ('ndk/', 'clang', 'Unix Makefiles', 'checked', {'ANDROID_ABI':'arm64-v8a', 'ANDROID_NATIVE_API_LEVEL':'19', 'ANDROID_PLATFORM':'19'}),
}

# Many builds of vvdec will produce the same outputs given the same input
# sequence and command line. The 'build group' string identifies these
# groups of encoder builds which are expected to match outputs

# Supported keyword arguments:
#   CFLAGS - directly assigned to CMAKE CFLAG args (intended for -m32)
#   CC,CXX - are set in the environment for cmake for selecting compilers
#   PATH   - this path is inserted into PATH for cmake, build and encoder runs
#            intended for MinGW/bin folder

# short-hand strings for CMAKE options, feel free to add more
#    'platform' : '-DCMAKE_GENERATOR_PLATFORM=x64'
option_strings = {
    'warn'    : '-DWARNINGS_AS_ERRORS=ON',
    'checked' : '-DCHECKED_BUILD=ON',
    'ftrapv'  : '-DENABLE_AGGRESSIVE_CHECKS=ON',
    'debug'   : '-DCMAKE_BUILD_TYPE=Debug',
    'reldeb'  : '-DCMAKE_BUILD_TYPE=RelWithDebInfo',
    'static'  : '-DENABLE_SHARED=OFF',
    'noasm'   : '-DENABLE_ASSEMBLY=OFF',
    'win64'     : '-A x64',
    'win32'     : '-A win32',
    'win-arm64' : '-A arm64',
    'win-arm32' : '-A arm',
}
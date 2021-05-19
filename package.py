# -*- coding: utf-8 -*-

name = 'oidn'

version = '1.4.0-ta.1.0.0'

authors = [
    'alex.fuller',
]

variants = [
    ['platform-windows', 'arch-x64', 'os-windows-10'],
    ['platform-linux', 'arch-x86_64', 'os-centos-7'],
]

requires = [
    'tbb-2017+'
]

build_system = "cmake"

# At Tangent rez-release is external by default, 
# this forces a rez-release as an internal package
with scope("config") as c:
    import sys
    if 'win' in str(sys.platform):
        c.release_packages_path = "R:/ext"
    else:
        c.release_packages_path = "/r/ext"

# At Tangent we have a visual studio package which 
# exposes the visual studio compiler for rez.
@early()
def private_build_requires():
    import sys
    if 'win' in str(sys.platform):
        return ['cmake-3.18<3.20', 'visual_studio', 'ispc-1.15+', 'python-3'] #, 'oiio']
    else:
        return ['cmake-3.18<3.20', 'gcc-6', 'ispc-1.15+', 'python-3'] #, 'oiio']

# Main commands for rez build and environment
def commands():        
    env.OIDN_ROOT.set('{root}')
    split_versions = str(version).split('-')
    env.OIDN_VERSION.set(split_versions[0])

    env.PATH.append('{root}/bin')

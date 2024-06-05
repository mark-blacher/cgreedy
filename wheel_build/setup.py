import os
from setuptools import setup, find_packages

def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

setup(
    name='cgreedy',
    version='0.0.3',
    author='Mark Blacher and Sheela Orgler',
    description='A greedy algorithm using multiple cost functions for finding efficient contraction paths',
    long_description=read('../cgreedy/README.md'),
    long_description_content_type='text/markdown',
    packages=find_packages(where=os.path.join('..')),
    package_dir={'': '..'},
    package_data={
        'cgreedy': [
            'LICENSE.md',
            'README.md',
            'linux_arm64/*.so',
            'linux_x86/*.so',
            'mac_arm64/*.dylib',
            'mac_x86/*.dylib',
            'windows_x86/*.dll',
        ]
    },
    license='MIT',
    classifiers=[
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3',
    ],
    install_requires=[
        'numpy'
    ],
)

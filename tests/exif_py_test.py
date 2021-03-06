import os
import unittest
#move to the project root
file_path = os.path.dirname(os.path.realpath(__file__))
project_root = os.path.join(file_path, '..')
os.chdir(project_root)
# build the c extensions
from subprocess import call
call(["python", "setup.py", "build"])

# find the exif build directory
import glob
import sys
lib_dir = glob.glob(os.path.join(project_root, "build", "lib*"))[0]
sys.path.append(lib_dir)

import exif_py

class ExifPyTest(unittest.TestCase):
    def test_extracts_metadata(self):
        # TODO(evandowling): improve this set of golden headers to be more robust
        metadata = exif_py.Metadata(os.path.join(file_path, "test_data", "valid.jpg"))
        self.assertEquals(metadata['Exif.GPSInfo.GPSLatitude'], '41/1 53/1 23487/1000') 
    
    def test_missing_file(self):
        # TODO(evandowling): handle these as typed errors
        try:
            metadata = exif_py.Metadata(os.path.join(file_path, "test_data", "missing.jpg"))
            self.fail("Assertion Error should be raise for a missing file")
        except AssertionError:
            success = True

    def test_invalid_file(self):
        # TODO(evandowling): handle these as typed errors
        try:
            metadata = exif_py.Metadata(os.path.join(file_path, "test_data", "invalid.jpg"))
            self.fail("Assertion Error should be raise for a invalid file")
        except AssertionError:
            success = True


if __name__ == "__main__":
    unittest.main()

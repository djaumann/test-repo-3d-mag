import os, shutil, git
from git import Repo


def onerror(func, path, exc_info):
    """
    Error handler for ``shutil.rmtree``.

    If the error is due to an access error (read only file)
    it attempts to add write permission and then retries.

    If the error is for another reason it re-raises the error.
    
    Usage : ``shutil.rmtree(path, onerror=onerror)``
    """
    import stat
    # Is the error an access error?
    if not os.access(path, os.W_OK):
        os.chmod(path, stat.S_IWUSR)
        func(path)
    else:
        raise


# Sources from TLx493D repo
src_path = ["./temp/src/tlx493d/", "./temp/src/framework/arduino/", "./temp/src/interfaces/" ]
examples_path = "./temp/examples/framework/arduino/"
test_path = "./temp/test/" 
# Destination paths in Arduino repo
dst_src_path = "./src/"
dst_examples_path = "./examples/"
dst_test_path = "./test/"
dst_version_file = "./version_info.txt"


# Clone latest state of the repository
if os.path.isdir("./temp") :
   shutil.rmtree("./temp", onerror=onerror)

repo = Repo.clone_from("https://bitbucket.vih.infineon.com/scm/xfpl/magnetic-3d-sensor-tlx493d.git", "./temp")
git_d = repo.git
# git_d.checkout("feature/DESMAKERS-3616-create-the-doxygen-documentation")

# Get all the source files
if os.path.exists(dst_src_path):
    shutil.rmtree(dst_src_path, onerror=onerror)

for path in src_path:
    shutil.copytree(path, dst_src_path, dirs_exist_ok=True)

    dir_list = os.listdir(dst_src_path)

    for file in dir_list:
        full_path = os.path.join(dst_src_path, file)
        if os.path.isdir(full_path):
            sub_dir_list = os.listdir(full_path)
            for sub_file in sub_dir_list:
                sub_dir_path = os.path.join(full_path, sub_file)
                shutil.move(sub_dir_path, dst_src_path)
            os.rmdir(full_path)
            dir_list.extend(sub_dir_list)


# Get all the examples
if os.path.exists(dst_examples_path):
    shutil.rmtree(dst_examples_path, onerror=onerror)

os.mkdir(dst_examples_path)

example_dir_list = os.listdir(examples_path)

for file in example_dir_list:
    name = file.removesuffix(".ino")
    name = os.path.join(dst_examples_path, name)
    os.mkdir(name)
    full_name = os.path.join(examples_path, file)
    shutil.copy(full_name, name)


# Get all the tests
if os.path.exists(dst_test_path):
    shutil.rmtree(dst_test_path, onerror=onerror)

os.mkdir(dst_test_path)

shutil.copytree(test_path, dst_test_path, dirs_exist_ok=True)
shutil.rmtree(dst_test_path + "unit/src/framework/mtb/", onerror=onerror)


# # Get repository meta data
# repo = git.Repo("./")
# tag_version = str(repo.tags[-1]) # Get tag
# tag_hash = str(repo.rev_parse("master")) # Get hash

# if os.path.exists(dst_version_file):
#     os.remove(dst_version_file)
    
# with open(dst_version_file, "w") as f:
#     f.write("Current tag of the repository is: \t\t" + tag_version + "\n")
#     f.write("Current hash of the repository is: \t\t" + tag_hash)

# Remove temporary files
shutil.rmtree("./temp", onerror=onerror)
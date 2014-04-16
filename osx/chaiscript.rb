require 'formula'

class Chaiscript < Formula
  homepage 'http://chaiscript.com/'
  url 'https://github.com/ChaiScript/ChaiScript/archive/7cebc8d748444691e429828c42f02f6b1f727adb.zip' #need recent commits for it to build properly for 10.9
  version '7ceb'
  sha1 'cbe06ea33463c445920e9b7170fb62e50442126d'
  head 'https://github.com/ChaiScript/ChaiScript.git', :branch => 'ChaiScript_5_0_CPP_11' #need the 5.x branch for osx 10.9

  depends_on 'cmake' => :build

  def install
    system "cmake", ".", "-DCMAKE_INSTALL_PREFIX=#{prefix}"
    system "make"
    #system "make", "test" 
    system "make", "install"
    lib.install "libchaiscript_stdlib.so" #make install forgets this vital file
  end

  test do
    system "false"
  end
end

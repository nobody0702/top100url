# top100url
Give a 100GB urls file, find the top 100 frequency url.



My solution:
![image](https://github.com/nobody0702/top100url/blob/master/pic/Screen%20Shot%202020-04-11%20at%208.43.59%20PM.png)

# Usage Example:
## Generate Url data
   ```
   #include "test/gen/data_gen.hpp"
   int main(){
       gen_data(100,"${local_path}");
       return 0;
   }
   ```
## Run top 100
   ```
   #include "runner.hpp"
   #include "util/file.hpp"
   int main(){
       file in("${input_file}");
       file out("${output_file}");
       runner r(&in,&out);
       r.run();
       return 0;
   }
   ```


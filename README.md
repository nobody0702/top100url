# top100url
Give a 100GB urls file, suppose you have only 1G memory, find the top 100 frequency url.


## partitioner:
  partitioner can partition a file into numbers of partition, there are two kind of partition function:
  1. range partition:
     range partition gets equally distributed address ranges of a input file.
  2. hash partition:
     hash partition use hash function std::hash<std::string>h to hash url and mod num_partition as partition id. repartition means partition a file that cannot merge using 1G memory, repartition hash the url one more times and get the partition id.
## aggregator:
  aggregator can aggregate a file, it read file into memory range by range, and output aggregated result to disk.
## merger:
  merger can merge a file into top k heap (if file size less than AGGREGATE_BYTES = 300M).
## statistic:
  statistic have two elements in memory: 
  1.topk_pq: one is top k heap, it stores top k (100) aggregated urls cnts; 
  
  2. sample_map: other is optional, sample map is a map stores sampled urls aggregation data,it ramdonly sample and got top k*100 frequency urls, and statistic these sampled urls in memory instead of disk. This is because sampled data with top k*100 will more likely to be top k frequency, and compute these url in memory will much faster than compute in disk.
## runner:
  runner scheduled tasks and run our main algorithm:
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
# Runtime:
  enviornment: 2.4GHZ intel i9
  1G memory 8 cores
  


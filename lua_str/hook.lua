print("hook init 1111");



local lj_new_fun_ptr = 0x19300a0

if(hook_newstr)      
then
   hook_newstr(lj_new_fun_ptr)
end



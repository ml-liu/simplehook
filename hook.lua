print("hook init");

print(set_hook)

if(set_hook)
then
  set_hook(0x40b120,"PLLLL","hook_notify1");
end

function hook_notify1(tid,block,osize,nsize)

--   print(get_current_stack())
   print(string.format("thread:%x,block=%d,osize=%d nsize=%d", tid,block,osize,nsize));
end

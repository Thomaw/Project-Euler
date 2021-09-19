%{
Each new term in the Fibonacci sequence is generated by adding the previous two terms. By starting with 1 and 2, the first 10 terms will be:

1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
%}

u=zeros(1,100)
u(1)=1
u(2)=2

p=0

    for i=3:50
        u(i)=u(i-1)+u(i-2)
    end
    

            
for j=1:length(u)
    if u(j)~=0 && u(j) < 4*10^6 && mod(u(j),2)== 0
        p=p+u(j)
    end
end
                          

            
p

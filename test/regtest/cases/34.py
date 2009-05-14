
desc = "test the type() function"

filedata="""
{$
    setl { a : [ 0, 1, [2], 3, { "foo" : 1 } ],
           d : { "a" : [1,2,3] },
           i : 10,
           f : 10.01,
           b : true
         }

    setl { ar1 : a,
           ar2 : a[2],
           ar3 : d.a,
           dr1 : d,
           dr2 : a[4],
           ir : i,
           fr : f,
           br : b }

%}
%{type(a)} %{type(ar1)} %{type(ar2)} %{type(ar3)}
%{type(d)} %{type(dr1)} %{type(dr2)}
%{type(i)} %{type(ir)}
%{type(f)} %{type(fr)}
%{type(b)} %{type(br)}
%{type(foo)}
"""

outcome = """
list list list list
dict dict dict
int int
float float
bool bool
undef
"""

          
           
           


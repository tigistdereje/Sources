LIB "tst.lib"; tst_init();
  ring r=0,(x,y,z),dp;
  ideal i=maxideal(2);
  ideal j=std(i);
  poly f=x+y2+z3;
  vector v=[f,1];
  qring q=j;
  poly f=fetch(r,f);
  f;
  vector v=fetch(r,v);
  v;
  ideal i=fetch(r,i);
  i;
  ring rr=0,(a,b,c),lp;
  poly f=fetch(q,f);
  f;
  vector v=fetch(r,v);
  v;
  ideal k=fetch(q,i);
  k;
tst_status(1);$

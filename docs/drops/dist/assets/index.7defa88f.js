`):"",r.downloadName=`${r.tcname.trim()} [mlvl-${r.mlvl}] [p-${r.players}] [mf-${r.mf}]`,await l(),r.doingIt=!1)}function m(u){for(let v in qe)if(qe[v].classid==u)return v;return""}function d(u,v){var b=document.createElement("a");b.download=v,b.href=u,document.body.appendChild(b),b.click(),document.body.removeChild(b)}function L(){r.output.trim().length&&d("data:text/html,"+r.output,`${r.downloadName}.txt`)}return(u,v)=>(ia(),ta("div",null,[O("div",BM,[O("div",UM,[SM,Te(O("select",{class:"form-select",type:"text","onUpdate:modelValue":v[0]||(v[0]=b=>la(r).tcname=b)},[(ia(!0),ta(X,null,bl(Object.values(la(re)).sort((b,H)=>b.lineNumber-H.lineNumber),(b,H)=>(ia(),ta("option",{key:H,value:b["Treasure Class"]},ie(b["Treasure Class"]),9,GM))),128))],512),[[c1,la(r).tcname]])]),O("div",EM,[zM,Te(O("input",{class:"form-control",type:"number",min:"1",max:"110","onUpdate:modelValue":v[1]||(v[1]=b=>la(r).mlvl=b)},null,512),[[xl,la(r).mlvl,void 0,{number:!0}]])]),O("div",_M,[DM,Te(O("input",{class:"form-control",type:"number",min:"1",max:"8","onUpdate:modelValue":v[2]||(v[2]=b=>la(r).players=b)},null,512),[[xl,la(r).players,void 0,{number:!0}]])]),O("div",JM,[FM,Te(O("input",{class:"form-control",type:"number",min:"0",max:"1167","onUpdate:modelValue":v[3]||(v[3]=b=>la(r).mf=b)},null,512),[[xl,la(r).mf,void 0,{number:!0}]])]),O("div",OM,[O("button",{type:"button",class:"btn btn-primary",onClick:s,disabled:la(r).doingIt},"Do it!",8,RM)]),O("div",jM,[O("button",{type:"button",class:"btn btn-primary",onClick:L,disabled:!la(r).output.trim().length||la(r).doingIt},"Download",8,WM)])]),la(r).downloadName.length?(ia(),ta("div",KM,"Filename: "+ie(la(r).downloadName)+".txt",1)):Ha("",!0),O("table",QM,[$M,O("tbody",null,[(ia(!0),ta(X,null,bl(la(r).output.split(`
`).filter(b=>b.length),(b,H)=>(ia(),ta("tr",{key:H,class:Ke({"table-info":la(r).rowSelect===H})},[(ia(!0),ta(X,null,bl(b.split(" "),(I,w)=>(ia(),ta(X,{key:w},[O("td",null,[Ua(ie(I)+" ",1),w===0?(ia(),ta(X,{key:0},[Ua("("+ie(m(I))+")",1)],64)):Ha("",!0),w===1&&I==2?(ia(),ta(X,{key:1},[VM],64)):Ha("",!0),w===1&&I==3?(ia(),ta(X,{key:2},[YM],64)):Ha("",!0),w===1&&I==4?(ia(),ta(X,{key:3},[ZM],64)):Ha("",!0),w===1&&I==5?(ia(),ta(X,{key:4},[XM],64)):Ha("",!0),w===1&&I==6?(ia(),ta(X,{key:5},[a6],64)):Ha("",!0),w===1&&I==7?(ia(),ta(X,{key:6},[e6],64)):Ha("",!0)]),w===2?(ia(),ta("td",l6,"~"+ie(Math.max(Math.round(Number(I)),1))+":"+ie(Math.max(Math.round(1/Number(I)),1)),1)):Ha("",!0)],64))),128))],2))),128))])])]))}};m1(i6).mount("#app");
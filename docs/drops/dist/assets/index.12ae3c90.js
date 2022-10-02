const _n=function(){const a=document.createElement("link").relList;if(a&&a.supports&&a.supports("modulepreload"))return;for(const n of document.querySelectorAll('link[rel="modulepreload"]'))i(n);new MutationObserver(n=>{for(const t of n)if(t.type==="childList")for(const l of t.addedNodes)l.tagName==="LINK"&&l.rel==="modulepreload"&&i(l)}).observe(document,{childList:!0,subtree:!0});function r(n){const t={};return n.integrity&&(t.integrity=n.integrity),n.referrerpolicy&&(t.referrerPolicy=n.referrerpolicy),n.crossorigin==="use-credentials"?t.credentials="include":n.crossorigin==="anonymous"?t.credentials="omit":t.credentials="same-origin",t}function i(n){if(n.ep)return;n.ep=!0;const t=r(n);fetch(n.href,t)}};_n();function zr(e,a){const r=Object.create(null),i=e.split(",");for(let n=0;n<i.length;n++)r[i[n]]=!0;return a?n=>!!r[n.toLowerCase()]:n=>!!r[n]}const Vn="itemscope,allowfullscreen,formnovalidate,ismap,nomodule,novalidate,readonly",Jn=zr(Vn);function ji(e){return!!e||e===""}function ar(e){if(B(e)){const a={};for(let r=0;r<e.length;r++){const i=e[r],n=se(i)?Yn(i):ar(i);if(n)for(const t in n)a[t]=n[t]}return a}else{if(se(e))return e;if(oe(e))return e}}const Qn=/;(?![^(]*\))/g,Kn=/:(.+)/;function Yn(e){const a={};return e.split(Qn).forEach(r=>{if(r){const i=r.split(Kn);i.length>1&&(a[i[0].trim()]=i[1].trim())}}),a}function Fr(e){let a="";if(se(e))a=e;else if(B(e))for(let r=0;r<e.length;r++){const i=Fr(e[r]);i&&(a+=i+" ")}else if(oe(e))for(const r in e)e[r]&&(a+=r+" ");return a.trim()}function Xn(e,a){if(e.length!==a.length)return!1;let r=!0;for(let i=0;r&&i<e.length;i++)r=rr(e[i],a[i]);return r}function rr(e,a){if(e===a)return!0;let r=ci(e),i=ci(a);if(r||i)return r&&i?e.getTime()===a.getTime():!1;if(r=B(e),i=B(a),r||i)return r&&i?Xn(e,a):!1;if(r=oe(e),i=oe(a),r||i){if(!r||!i)return!1;const n=Object.keys(e).length,t=Object.keys(a).length;if(n!==t)return!1;for(const l in e){const s=e.hasOwnProperty(l),m=a.hasOwnProperty(l);if(s&&!m||!s&&m||!rr(e[l],a[l]))return!1}}return String(e)===String(a)}function _i(e,a){return e.findIndex(r=>rr(r,a))}const Te=e=>se(e)?e:e==null?"":B(e)||oe(e)&&(e.toString===Qi||!z(e.toString))?JSON.stringify(e,Vi,2):String(e),Vi=(e,a)=>a&&a.__v_isRef?Vi(e,a.value):Aa(a)?{[`Map(${a.size})`]:[...a.entries()].reduce((r,[i,n])=>(r[`${i} =>`]=n,r),{})}:nr(a)?{[`Set(${a.size})`]:[...a.values()]}:oe(a)&&!B(a)&&!Ki(a)?String(a):a,$={},ba=[],De=()=>{},$n=()=>!1,Zn=/^on[^a-z]/,ir=e=>Zn.test(e),Wr=e=>e.startsWith("onUpdate:"),ge=Object.assign,jr=(e,a)=>{const r=e.indexOf(a);r>-1&&e.splice(r,1)},el=Object.prototype.hasOwnProperty,_=(e,a)=>el.call(e,a),B=Array.isArray,Aa=e=>lr(e)==="[object Map]",nr=e=>lr(e)==="[object Set]",ci=e=>e instanceof Date,z=e=>typeof e=="function",se=e=>typeof e=="string",_r=e=>typeof e=="symbol",oe=e=>e!==null&&typeof e=="object",Ji=e=>oe(e)&&z(e.then)&&z(e.catch),Qi=Object.prototype.toString,lr=e=>Qi.call(e),al=e=>lr(e).slice(8,-1),Ki=e=>lr(e)==="[object Object]",Vr=e=>se(e)&&e!=="NaN"&&e[0]!=="-"&&""+parseInt(e,10)===e,Wa=zr(",key,ref,ref_for,ref_key,onVnodeBeforeMount,onVnodeMounted,onVnodeBeforeUpdate,onVnodeUpdated,onVnodeBeforeUnmount,onVnodeUnmounted"),tr=e=>{const a=Object.create(null);return r=>a[r]||(a[r]=e(r))},rl=/-(\w)/g,Na=tr(e=>e.replace(rl,(a,r)=>r?r.toUpperCase():"")),il=/\B([A-Z])/g,ka=tr(e=>e.replace(il,"-$1").toLowerCase()),Yi=tr(e=>e.charAt(0).toUpperCase()+e.slice(1)),Mr=tr(e=>e?`on${Yi(e)}`:""),Ja=(e,a)=>!Object.is(e,a),ja=(e,a)=>{for(let r=0;r<e.length;r++)e[r](a)},Qa=(e,a,r)=>{Object.defineProperty(e,a,{configurable:!0,enumerable:!1,value:r})},kr=e=>{const a=parseFloat(e);return isNaN(a)?e:a};let mi;const nl=()=>mi||(mi=typeof globalThis!="undefined"?globalThis:typeof self!="undefined"?self:typeof window!="undefined"?window:typeof global!="undefined"?global:{});let Ge;class ll{constructor(a=!1){this.active=!0,this.effects=[],this.cleanups=[],!a&&Ge&&(this.parent=Ge,this.index=(Ge.scopes||(Ge.scopes=[])).push(this)-1)}run(a){if(this.active){const r=Ge;try{return Ge=this,a()}finally{Ge=r}}}on(){Ge=this}off(){Ge=this.parent}stop(a){if(this.active){let r,i;for(r=0,i=this.effects.length;r<i;r++)this.effects[r].stop();for(r=0,i=this.cleanups.length;r<i;r++)this.cleanups[r]();if(this.scopes)for(r=0,i=this.scopes.length;r<i;r++)this.scopes[r].stop(!0);if(this.parent&&!a){const n=this.parent.scopes.pop();n&&n!==this&&(this.parent.scopes[this.index]=n,n.index=this.index)}this.active=!1}}}function tl(e,a=Ge){a&&a.active&&a.effects.push(e)}const Jr=e=>{const a=new Set(e);return a.w=0,a.n=0,a},Xi=e=>(e.w&Ze)>0,$i=e=>(e.n&Ze)>0,ol=({deps:e})=>{if(e.length)for(let a=0;a<e.length;a++)e[a].w|=Ze},sl=e=>{const{deps:a}=e;if(a.length){let r=0;for(let i=0;i<a.length;i++){const n=a[i];Xi(n)&&!$i(n)?n.delete(e):a[r++]=n,n.w&=~Ze,n.n&=~Ze}a.length=r}},Cr=new WeakMap;let Sa=0,Ze=1;const yr=30;let Se;const ca=Symbol(""),Lr=Symbol("");class Qr{constructor(a,r=null,i){this.fn=a,this.scheduler=r,this.active=!0,this.deps=[],this.parent=void 0,tl(this,i)}run(){if(!this.active)return this.fn();let a=Se,r=Xe;for(;a;){if(a===this)return;a=a.parent}try{return this.parent=Se,Se=this,Xe=!0,Ze=1<<++Sa,Sa<=yr?ol(this):pi(this),this.fn()}finally{Sa<=yr&&sl(this),Ze=1<<--Sa,Se=this.parent,Xe=r,this.parent=void 0,this.deferStop&&this.stop()}}stop(){Se===this?this.deferStop=!0:this.active&&(pi(this),this.onStop&&this.onStop(),this.active=!1)}}function pi(e){const{deps:a}=e;if(a.length){for(let r=0;r<a.length;r++)a[r].delete(e);a.length=0}}let Xe=!0;const Zi=[];function Ca(){Zi.push(Xe),Xe=!1}function ya(){const e=Zi.pop();Xe=e===void 0?!0:e}function fe(e,a,r){if(Xe&&Se){let i=Cr.get(e);i||Cr.set(e,i=new Map);let n=i.get(r);n||i.set(r,n=Jr()),en(n)}}function en(e,a){let r=!1;Sa<=yr?$i(e)||(e.n|=Ze,r=!Xi(e)):r=!e.has(Se),r&&(e.add(Se),Se.deps.push(e))}function _e(e,a,r,i,n,t){const l=Cr.get(e);if(!l)return;let s=[];if(a==="clear")s=[...l.values()];else if(r==="length"&&B(e))l.forEach((m,h)=>{(h==="length"||h>=i)&&s.push(m)});else switch(r!==void 0&&s.push(l.get(r)),a){case"add":B(e)?Vr(r)&&s.push(l.get("length")):(s.push(l.get(ca)),Aa(e)&&s.push(l.get(Lr)));break;case"delete":B(e)||(s.push(l.get(ca)),Aa(e)&&s.push(l.get(Lr)));break;case"set":Aa(e)&&s.push(l.get(ca));break}if(s.length===1)s[0]&&Tr(s[0]);else{const m=[];for(const h of s)h&&m.push(...h);Tr(Jr(m))}}function Tr(e,a){for(const r of B(e)?e:[...e])(r!==Se||r.allowRecurse)&&(r.scheduler?r.scheduler():r.run())}const cl=zr("__proto__,__v_isRef,__isVue"),an=new Set(Object.getOwnPropertyNames(Symbol).map(e=>Symbol[e]).filter(_r)),ml=Kr(),pl=Kr(!1,!0),dl=Kr(!0),di=ul();function ul(){const e={};return["includes","indexOf","lastIndexOf"].forEach(a=>{e[a]=function(...r){const i=K(this);for(let t=0,l=this.length;t<l;t++)fe(i,"get",t+"");const n=i[a](...r);return n===-1||n===!1?i[a](...r.map(K)):n}}),["push","pop","shift","unshift","splice"].forEach(a=>{e[a]=function(...r){Ca();const i=K(this)[a].apply(this,r);return ya(),i}}),e}function Kr(e=!1,a=!1){return function(i,n,t){if(n==="__v_isReactive")return!e;if(n==="__v_isReadonly")return e;if(n==="__v_isShallow")return a;if(n==="__v_raw"&&t===(e?a?Sl:on:a?tn:ln).get(i))return i;const l=B(i);if(!e&&l&&_(di,n))return Reflect.get(di,n,t);const s=Reflect.get(i,n,t);return(_r(n)?an.has(n):cl(n))||(e||fe(i,"get",n),a)?s:ue(s)?!l||!Vr(n)?s.value:s:oe(s)?e?sn(s):sr(s):s}}const gl=rn(),Ml=rn(!0);function rn(e=!1){return function(r,i,n,t){let l=r[i];if(Ea(l)&&ue(l)&&!ue(n))return!1;if(!e&&!Ea(n)&&(cn(n)||(n=K(n),l=K(l)),!B(r)&&ue(l)&&!ue(n)))return l.value=n,!0;const s=B(r)&&Vr(i)?Number(i)<r.length:_(r,i),m=Reflect.set(r,i,n,t);return r===K(t)&&(s?Ja(n,l)&&_e(r,"set",i,n):_e(r,"add",i,n)),m}}function hl(e,a){const r=_(e,a);e[a];const i=Reflect.deleteProperty(e,a);return i&&r&&_e(e,"delete",a,void 0),i}function vl(e,a){const r=Reflect.has(e,a);return(!_r(a)||!an.has(a))&&fe(e,"has",a),r}function Hl(e){return fe(e,"iterate",B(e)?"length":ca),Reflect.ownKeys(e)}const nn={get:ml,set:gl,deleteProperty:hl,has:vl,ownKeys:Hl},bl={get:dl,set(e,a){return!0},deleteProperty(e,a){return!0}},Al=ge({},nn,{get:pl,set:Ml}),Yr=e=>e,or=e=>Reflect.getPrototypeOf(e);function qa(e,a,r=!1,i=!1){e=e.__v_raw;const n=K(e),t=K(a);a!==t&&!r&&fe(n,"get",a),!r&&fe(n,"get",t);const{has:l}=or(n),s=i?Yr:r?ei:Zr;if(l.call(n,a))return s(e.get(a));if(l.call(n,t))return s(e.get(t));e!==n&&e.get(a)}function Ga(e,a=!1){const r=this.__v_raw,i=K(r),n=K(e);return e!==n&&!a&&fe(i,"has",e),!a&&fe(i,"has",n),e===n?r.has(e):r.has(e)||r.has(n)}function Ua(e,a=!1){return e=e.__v_raw,!a&&fe(K(e),"iterate",ca),Reflect.get(e,"size",e)}function ui(e){e=K(e);const a=K(this);return or(a).has.call(a,e)||(a.add(e),_e(a,"add",e,e)),this}function gi(e,a){a=K(a);const r=K(this),{has:i,get:n}=or(r);let t=i.call(r,e);t||(e=K(e),t=i.call(r,e));const l=n.call(r,e);return r.set(e,a),t?Ja(a,l)&&_e(r,"set",e,a):_e(r,"add",e,a),this}function Mi(e){const a=K(this),{has:r,get:i}=or(a);let n=r.call(a,e);n||(e=K(e),n=r.call(a,e)),i&&i.call(a,e);const t=a.delete(e);return n&&_e(a,"delete",e,void 0),t}function hi(){const e=K(this),a=e.size!==0,r=e.clear();return a&&_e(e,"clear",void 0,void 0),r}function Oa(e,a){return function(i,n){const t=this,l=t.__v_raw,s=K(l),m=a?Yr:e?ei:Zr;return!e&&fe(s,"iterate",ca),l.forEach((h,A)=>i.call(n,m(h),m(A),t))}}function za(e,a,r){return function(...i){const n=this.__v_raw,t=K(n),l=Aa(t),s=e==="entries"||e===Symbol.iterator&&l,m=e==="keys"&&l,h=n[e](...i),A=r?Yr:a?ei:Zr;return!a&&fe(t,"iterate",m?Lr:ca),{next(){const{value:L,done:f}=h.next();return f?{value:L,done:f}:{value:s?[A(L[0]),A(L[1])]:A(L),done:f}},[Symbol.iterator](){return this}}}}function Je(e){return function(...a){return e==="delete"?!1:this}}function xl(){const e={get(t){return qa(this,t)},get size(){return Ua(this)},has:Ga,add:ui,set:gi,delete:Mi,clear:hi,forEach:Oa(!1,!1)},a={get(t){return qa(this,t,!1,!0)},get size(){return Ua(this)},has:Ga,add:ui,set:gi,delete:Mi,clear:hi,forEach:Oa(!1,!0)},r={get(t){return qa(this,t,!0)},get size(){return Ua(this,!0)},has(t){return Ga.call(this,t,!0)},add:Je("add"),set:Je("set"),delete:Je("delete"),clear:Je("clear"),forEach:Oa(!0,!1)},i={get(t){return qa(this,t,!0,!0)},get size(){return Ua(this,!0)},has(t){return Ga.call(this,t,!0)},add:Je("add"),set:Je("set"),delete:Je("delete"),clear:Je("clear"),forEach:Oa(!0,!0)};return["keys","values","entries",Symbol.iterator].forEach(t=>{e[t]=za(t,!1,!1),r[t]=za(t,!0,!1),a[t]=za(t,!1,!0),i[t]=za(t,!0,!0)}),[e,r,a,i]}const[Nl,fl,kl,Cl]=xl();function Xr(e,a){const r=a?e?Cl:kl:e?fl:Nl;return(i,n,t)=>n==="__v_isReactive"?!e:n==="__v_isReadonly"?e:n==="__v_raw"?i:Reflect.get(_(r,n)&&n in i?r:i,n,t)}const yl={get:Xr(!1,!1)},Ll={get:Xr(!1,!0)},Tl={get:Xr(!0,!1)},ln=new WeakMap,tn=new WeakMap,on=new WeakMap,Sl=new WeakMap;function wl(e){switch(e){case"Object":case"Array":return 1;case"Map":case"Set":case"WeakMap":case"WeakSet":return 2;default:return 0}}function Dl(e){return e.__v_skip||!Object.isExtensible(e)?0:wl(al(e))}function sr(e){return Ea(e)?e:$r(e,!1,nn,yl,ln)}function Pl(e){return $r(e,!1,Al,Ll,tn)}function sn(e){return $r(e,!0,bl,Tl,on)}function $r(e,a,r,i,n){if(!oe(e)||e.__v_raw&&!(a&&e.__v_isReactive))return e;const t=n.get(e);if(t)return t;const l=Dl(e);if(l===0)return e;const s=new Proxy(e,l===2?i:r);return n.set(e,s),s}function xa(e){return Ea(e)?xa(e.__v_raw):!!(e&&e.__v_isReactive)}function Ea(e){return!!(e&&e.__v_isReadonly)}function cn(e){return!!(e&&e.__v_isShallow)}function mn(e){return xa(e)||Ea(e)}function K(e){const a=e&&e.__v_raw;return a?K(a):e}function pn(e){return Qa(e,"__v_skip",!0),e}const Zr=e=>oe(e)?sr(e):e,ei=e=>oe(e)?sn(e):e;function Il(e){Xe&&Se&&(e=K(e),en(e.dep||(e.dep=Jr())))}function El(e,a){e=K(e),e.dep&&Tr(e.dep)}function ue(e){return!!(e&&e.__v_isRef===!0)}function Q(e){return ue(e)?e.value:e}const Rl={get:(e,a,r)=>Q(Reflect.get(e,a,r)),set:(e,a,r,i)=>{const n=e[a];return ue(n)&&!ue(r)?(n.value=r,!0):Reflect.set(e,a,r,i)}};function dn(e){return xa(e)?e:new Proxy(e,Rl)}class Bl{constructor(a,r,i,n){this._setter=r,this.dep=void 0,this.__v_isRef=!0,this._dirty=!0,this.effect=new Qr(a,()=>{this._dirty||(this._dirty=!0,El(this))}),this.effect.computed=this,this.effect.active=this._cacheable=!n,this.__v_isReadonly=i}get value(){const a=K(this);return Il(a),(a._dirty||!a._cacheable)&&(a._dirty=!1,a._value=a.effect.run()),a._value}set value(a){this._setter(a)}}function ql(e,a,r=!1){let i,n;const t=z(e);return t?(i=e,n=De):(i=e.get,n=e.set),new Bl(i,n,t||!n,r)}function $e(e,a,r,i){let n;try{n=i?e(...i):e()}catch(t){cr(t,a,r)}return n}function Ce(e,a,r,i){if(z(e)){const t=$e(e,a,r,i);return t&&Ji(t)&&t.catch(l=>{cr(l,a,r)}),t}const n=[];for(let t=0;t<e.length;t++)n.push(Ce(e[t],a,r,i));return n}function cr(e,a,r,i=!0){const n=a?a.vnode:null;if(a){let t=a.parent;const l=a.proxy,s=r;for(;t;){const h=t.ec;if(h){for(let A=0;A<h.length;A++)if(h[A](e,l,s)===!1)return}t=t.parent}const m=a.appContext.config.errorHandler;if(m){$e(m,null,10,[e,l,s]);return}}Gl(e,r,n,i)}function Gl(e,a,r,i=!0){console.error(e)}let Ka=!1,Sr=!1;const Ne=[];let We=0;const Da=[];let wa=null,va=0;const Pa=[];let Ke=null,Ha=0;const un=Promise.resolve();let ai=null,wr=null;function Ul(e){const a=ai||un;return e?a.then(this?e.bind(this):e):a}function Ol(e){let a=We+1,r=Ne.length;for(;a<r;){const i=a+r>>>1;Ra(Ne[i])<e?a=i+1:r=i}return a}function gn(e){(!Ne.length||!Ne.includes(e,Ka&&e.allowRecurse?We+1:We))&&e!==wr&&(e.id==null?Ne.push(e):Ne.splice(Ol(e.id),0,e),Mn())}function Mn(){!Ka&&!Sr&&(Sr=!0,ai=un.then(Hn))}function zl(e){const a=Ne.indexOf(e);a>We&&Ne.splice(a,1)}function hn(e,a,r,i){B(e)?r.push(...e):(!a||!a.includes(e,e.allowRecurse?i+1:i))&&r.push(e),Mn()}function Fl(e){hn(e,wa,Da,va)}function Wl(e){hn(e,Ke,Pa,Ha)}function ri(e,a=null){if(Da.length){for(wr=a,wa=[...new Set(Da)],Da.length=0,va=0;va<wa.length;va++)wa[va]();wa=null,va=0,wr=null,ri(e,a)}}function vn(e){if(Pa.length){const a=[...new Set(Pa)];if(Pa.length=0,Ke){Ke.push(...a);return}for(Ke=a,Ke.sort((r,i)=>Ra(r)-Ra(i)),Ha=0;Ha<Ke.length;Ha++)Ke[Ha]();Ke=null,Ha=0}}const Ra=e=>e.id==null?1/0:e.id;function Hn(e){Sr=!1,Ka=!0,ri(e),Ne.sort((r,i)=>Ra(r)-Ra(i));const a=De;try{for(We=0;We<Ne.length;We++){const r=Ne[We];r&&r.active!==!1&&$e(r,null,14)}}finally{We=0,Ne.length=0,vn(),Ka=!1,ai=null,(Ne.length||Da.length||Pa.length)&&Hn(e)}}function jl(e,a,...r){if(e.isUnmounted)return;const i=e.vnode.props||$;let n=r;const t=a.startsWith("update:"),l=t&&a.slice(7);if(l&&l in i){const A=`${l==="modelValue"?"model":l}Modifiers`,{number:L,trim:f}=i[A]||$;f?n=r.map(q=>q.trim()):L&&(n=r.map(kr))}let s,m=i[s=Mr(a)]||i[s=Mr(Na(a))];!m&&t&&(m=i[s=Mr(ka(a))]),m&&Ce(m,e,6,n);const h=i[s+"Once"];if(h){if(!e.emitted)e.emitted={};else if(e.emitted[s])return;e.emitted[s]=!0,Ce(h,e,6,n)}}function bn(e,a,r=!1){const i=a.emitsCache,n=i.get(e);if(n!==void 0)return n;const t=e.emits;let l={},s=!1;if(!z(e)){const m=h=>{const A=bn(h,a,!0);A&&(s=!0,ge(l,A))};!r&&a.mixins.length&&a.mixins.forEach(m),e.extends&&m(e.extends),e.mixins&&e.mixins.forEach(m)}return!t&&!s?(i.set(e,null),null):(B(t)?t.forEach(m=>l[m]=null):ge(l,t),i.set(e,l),l)}function mr(e,a){return!e||!ir(a)?!1:(a=a.slice(2).replace(/Once$/,""),_(e,a[0].toLowerCase()+a.slice(1))||_(e,ka(a))||_(e,a))}let we=null,An=null;function Ya(e){const a=we;return we=e,An=e&&e.type.__scopeId||null,a}function _l(e,a=we,r){if(!a||e._n)return e;const i=(...n)=>{i._d&&yi(-1);const t=Ya(a),l=e(...n);return Ya(t),i._d&&yi(1),l};return i._n=!0,i._c=!0,i._d=!0,i}function hr(e){const{type:a,vnode:r,proxy:i,withProxy:n,props:t,propsOptions:[l],slots:s,attrs:m,emit:h,render:A,renderCache:L,data:f,setupState:q,ctx:W,inheritAttrs:j}=e;let U,V;const Me=Ya(e);try{if(r.shapeFlag&4){const Y=n||i;U=Ue(A.call(Y,Y,L,t,q,f,W)),V=m}else{const Y=a;U=Ue(Y.length>1?Y(t,{attrs:m,slots:s,emit:h}):Y(t,null)),V=a.props?m:Vl(m)}}catch(Y){Ia.length=0,cr(Y,e,1),U=je(Pe)}let le=U;if(V&&j!==!1){const Y=Object.keys(V),{shapeFlag:ce}=le;Y.length&&ce&7&&(l&&Y.some(Wr)&&(V=Jl(V,l)),le=da(le,V))}return r.dirs&&(le.dirs=le.dirs?le.dirs.concat(r.dirs):r.dirs),r.transition&&(le.transition=r.transition),U=le,Ya(Me),U}const Vl=e=>{let a;for(const r in e)(r==="class"||r==="style"||ir(r))&&((a||(a={}))[r]=e[r]);return a},Jl=(e,a)=>{const r={};for(const i in e)(!Wr(i)||!(i.slice(9)in a))&&(r[i]=e[i]);return r};function Ql(e,a,r){const{props:i,children:n,component:t}=e,{props:l,children:s,patchFlag:m}=a,h=t.emitsOptions;if(a.dirs||a.transition)return!0;if(r&&m>=0){if(m&1024)return!0;if(m&16)return i?vi(i,l,h):!!l;if(m&8){const A=a.dynamicProps;for(let L=0;L<A.length;L++){const f=A[L];if(l[f]!==i[f]&&!mr(h,f))return!0}}}else return(n||s)&&(!s||!s.$stable)?!0:i===l?!1:i?l?vi(i,l,h):!0:!!l;return!1}function vi(e,a,r){const i=Object.keys(a);if(i.length!==Object.keys(e).length)return!0;for(let n=0;n<i.length;n++){const t=i[n];if(a[t]!==e[t]&&!mr(r,t))return!0}return!1}function Kl({vnode:e,parent:a},r){for(;a&&a.subTree===e;)(e=a.vnode).el=r,a=a.parent}const Yl=e=>e.__isSuspense;function Xl(e,a){a&&a.pendingBranch?B(e)?a.effects.push(...e):a.effects.push(e):Wl(e)}function $l(e,a){if(me){let r=me.provides;const i=me.parent&&me.parent.provides;i===r&&(r=me.provides=Object.create(i)),r[e]=a}}function vr(e,a,r=!1){const i=me||we;if(i){const n=i.parent==null?i.vnode.appContext&&i.vnode.appContext.provides:i.parent.provides;if(n&&e in n)return n[e];if(arguments.length>1)return r&&z(a)?a.call(i.proxy):a}}const Hi={};function _a(e,a,r){return xn(e,a,r)}function xn(e,a,{immediate:r,deep:i,flush:n,onTrack:t,onTrigger:l}=$){const s=me;let m,h=!1,A=!1;if(ue(e)?(m=()=>e.value,h=cn(e)):xa(e)?(m=()=>e,i=!0):B(e)?(A=!0,h=e.some(xa),m=()=>e.map(V=>{if(ue(V))return V.value;if(xa(V))return sa(V);if(z(V))return $e(V,s,2)})):z(e)?a?m=()=>$e(e,s,2):m=()=>{if(!(s&&s.isUnmounted))return L&&L(),Ce(e,s,3,[f])}:m=De,a&&i){const V=m;m=()=>sa(V())}let L,f=V=>{L=U.onStop=()=>{$e(V,s,4)}};if(Ba)return f=De,a?r&&Ce(a,s,3,[m(),A?[]:void 0,f]):m(),De;let q=A?[]:Hi;const W=()=>{if(!!U.active)if(a){const V=U.run();(i||h||(A?V.some((Me,le)=>Ja(Me,q[le])):Ja(V,q)))&&(L&&L(),Ce(a,s,3,[V,q===Hi?void 0:q,f]),q=V)}else U.run()};W.allowRecurse=!!a;let j;n==="sync"?j=W:n==="post"?j=()=>He(W,s&&s.suspense):j=()=>{!s||s.isMounted?Fl(W):W()};const U=new Qr(m,j);return a?r?W():q=U.run():n==="post"?He(U.run.bind(U),s&&s.suspense):U.run(),()=>{U.stop(),s&&s.scope&&jr(s.scope.effects,U)}}function Zl(e,a,r){const i=this.proxy,n=se(e)?e.includes(".")?Nn(i,e):()=>i[e]:e.bind(i,i);let t;z(a)?t=a:(t=a.handler,r=a);const l=me;fa(this);const s=xn(n,t.bind(i),r);return l?fa(l):pa(),s}function Nn(e,a){const r=a.split(".");return()=>{let i=e;for(let n=0;n<r.length&&i;n++)i=i[r[n]];return i}}function sa(e,a){if(!oe(e)||e.__v_skip||(a=a||new Set,a.has(e)))return e;if(a.add(e),ue(e))sa(e.value,a);else if(B(e))for(let r=0;r<e.length;r++)sa(e[r],a);else if(nr(e)||Aa(e))e.forEach(r=>{sa(r,a)});else if(Ki(e))for(const r in e)sa(e[r],a);return e}function et(){const e={isMounted:!1,isLeaving:!1,isUnmounting:!1,leavingVNodes:new Map};return yn(()=>{e.isMounted=!0}),Ln(()=>{e.isUnmounting=!0}),e}const ke=[Function,Array],at={name:"BaseTransition",props:{mode:String,appear:Boolean,persisted:Boolean,onBeforeEnter:ke,onEnter:ke,onAfterEnter:ke,onEnterCancelled:ke,onBeforeLeave:ke,onLeave:ke,onAfterLeave:ke,onLeaveCancelled:ke,onBeforeAppear:ke,onAppear:ke,onAfterAppear:ke,onAppearCancelled:ke},setup(e,{slots:a}){const r=zt(),i=et();let n;return()=>{const t=a.default&&kn(a.default(),!0);if(!t||!t.length)return;let l=t[0];if(t.length>1){for(const j of t)if(j.type!==Pe){l=j;break}}const s=K(e),{mode:m}=s;if(i.isLeaving)return Hr(l);const h=bi(l);if(!h)return Hr(l);const A=Dr(h,s,i,r);Pr(h,A);const L=r.subTree,f=L&&bi(L);let q=!1;const{getTransitionKey:W}=h.type;if(W){const j=W();n===void 0?n=j:j!==n&&(n=j,q=!0)}if(f&&f.type!==Pe&&(!la(h,f)||q)){const j=Dr(f,s,i,r);if(Pr(f,j),m==="out-in")return i.isLeaving=!0,j.afterLeave=()=>{i.isLeaving=!1,r.update()},Hr(l);m==="in-out"&&h.type!==Pe&&(j.delayLeave=(U,V,Me)=>{const le=fn(i,f);le[String(f.key)]=f,U._leaveCb=()=>{V(),U._leaveCb=void 0,delete A.delayedLeave},A.delayedLeave=Me})}return l}}},rt=at;function fn(e,a){const{leavingVNodes:r}=e;let i=r.get(a.type);return i||(i=Object.create(null),r.set(a.type,i)),i}function Dr(e,a,r,i){const{appear:n,mode:t,persisted:l=!1,onBeforeEnter:s,onEnter:m,onAfterEnter:h,onEnterCancelled:A,onBeforeLeave:L,onLeave:f,onAfterLeave:q,onLeaveCancelled:W,onBeforeAppear:j,onAppear:U,onAfterAppear:V,onAppearCancelled:Me}=a,le=String(e.key),Y=fn(r,e),ce=(J,re)=>{J&&Ce(J,i,9,re)},Ie={mode:t,persisted:l,beforeEnter(J){let re=s;if(!r.isMounted)if(n)re=j||s;else return;J._leaveCb&&J._leaveCb(!0);const p=Y[le];p&&la(e,p)&&p.el._leaveCb&&p.el._leaveCb(),ce(re,[J])},enter(J){let re=m,p=h,u=A;if(!r.isMounted)if(n)re=U||m,p=V||h,u=Me||A;else return;let g=!1;const C=J._enterCb=S=>{g||(g=!0,S?ce(u,[J]):ce(p,[J]),Ie.delayedLeave&&Ie.delayedLeave(),J._enterCb=void 0)};re?(re(J,C),re.length<=1&&C()):C()},leave(J,re){const p=String(e.key);if(J._enterCb&&J._enterCb(!0),r.isUnmounting)return re();ce(L,[J]);let u=!1;const g=J._leaveCb=C=>{u||(u=!0,re(),C?ce(W,[J]):ce(q,[J]),J._leaveCb=void 0,Y[p]===e&&delete Y[p])};Y[p]=e,f?(f(J,g),f.length<=1&&g()):g()},clone(J){return Dr(J,a,r,i)}};return Ie}function Hr(e){if(pr(e))return e=da(e),e.children=null,e}function bi(e){return pr(e)?e.children?e.children[0]:void 0:e}function Pr(e,a){e.shapeFlag&6&&e.component?Pr(e.component.subTree,a):e.shapeFlag&128?(e.ssContent.transition=a.clone(e.ssContent),e.ssFallback.transition=a.clone(e.ssFallback)):e.transition=a}function kn(e,a=!1,r){let i=[],n=0;for(let t=0;t<e.length;t++){let l=e[t];const s=r==null?l.key:String(r)+String(l.key!=null?l.key:t);l.type===be?(l.patchFlag&128&&n++,i=i.concat(kn(l.children,a,s))):(a||l.type!==Pe)&&i.push(s!=null?da(l,{key:s}):l)}if(n>1)for(let t=0;t<i.length;t++)i[t].patchFlag=-2;return i}const Ir=e=>!!e.type.__asyncLoader,pr=e=>e.type.__isKeepAlive;function it(e,a){Cn(e,"a",a)}function nt(e,a){Cn(e,"da",a)}function Cn(e,a,r=me){const i=e.__wdc||(e.__wdc=()=>{let n=r;for(;n;){if(n.isDeactivated)return;n=n.parent}return e()});if(dr(a,i,r),r){let n=r.parent;for(;n&&n.parent;)pr(n.parent.vnode)&&lt(i,a,r,n),n=n.parent}}function lt(e,a,r,i){const n=dr(a,e,i,!0);Tn(()=>{jr(i[a],n)},r)}function dr(e,a,r=me,i=!1){if(r){const n=r[e]||(r[e]=[]),t=a.__weh||(a.__weh=(...l)=>{if(r.isUnmounted)return;Ca(),fa(r);const s=Ce(a,r,e,l);return pa(),ya(),s});return i?n.unshift(t):n.push(t),t}}const Ve=e=>(a,r=me)=>(!Ba||e==="sp")&&dr(e,a,r),tt=Ve("bm"),yn=Ve("m"),ot=Ve("bu"),st=Ve("u"),Ln=Ve("bum"),Tn=Ve("um"),ct=Ve("sp"),mt=Ve("rtg"),pt=Ve("rtc");function dt(e,a=me){dr("ec",e,a)}let Er=!0;function ut(e){const a=wn(e),r=e.proxy,i=e.ctx;Er=!1,a.beforeCreate&&Ai(a.beforeCreate,e,"bc");const{data:n,computed:t,methods:l,watch:s,provide:m,inject:h,created:A,beforeMount:L,mounted:f,beforeUpdate:q,updated:W,activated:j,deactivated:U,beforeDestroy:V,beforeUnmount:Me,destroyed:le,unmounted:Y,render:ce,renderTracked:Ie,renderTriggered:J,errorCaptured:re,serverPrefetch:p,expose:u,inheritAttrs:g,components:C,directives:S,filters:Z}=a;if(h&&gt(h,i,null,e.appContext.config.unwrapInjectedRef),l)for(const T in l){const P=l[T];z(P)&&(i[T]=P.bind(r))}if(n){const T=n.call(r,r);oe(T)&&(e.data=sr(T))}if(Er=!0,t)for(const T in t){const P=t[T],I=z(P)?P.bind(r,r):z(P.get)?P.get.bind(r,r):De,Ee=!z(P)&&z(P.set)?P.set.bind(r):De,F=Fn({get:I,set:Ee});Object.defineProperty(i,T,{enumerable:!0,configurable:!0,get:()=>F.value,set:ie=>F.value=ie})}if(s)for(const T in s)Sn(s[T],i,r,T);if(m){const T=z(m)?m.call(r):m;Reflect.ownKeys(T).forEach(P=>{$l(P,T[P])})}A&&Ai(A,e,"c");function R(T,P){B(P)?P.forEach(I=>T(I.bind(r))):P&&T(P.bind(r))}if(R(tt,L),R(yn,f),R(ot,q),R(st,W),R(it,j),R(nt,U),R(dt,re),R(pt,Ie),R(mt,J),R(Ln,Me),R(Tn,Y),R(ct,p),B(u))if(u.length){const T=e.exposed||(e.exposed={});u.forEach(P=>{Object.defineProperty(T,P,{get:()=>r[P],set:I=>r[P]=I})})}else e.exposed||(e.exposed={});ce&&e.render===De&&(e.render=ce),g!=null&&(e.inheritAttrs=g),C&&(e.components=C),S&&(e.directives=S)}function gt(e,a,r=De,i=!1){B(e)&&(e=Rr(e));for(const n in e){const t=e[n];let l;oe(t)?"default"in t?l=vr(t.from||n,t.default,!0):l=vr(t.from||n):l=vr(t),ue(l)&&i?Object.defineProperty(a,n,{enumerable:!0,configurable:!0,get:()=>l.value,set:s=>l.value=s}):a[n]=l}}function Ai(e,a,r){Ce(B(e)?e.map(i=>i.bind(a.proxy)):e.bind(a.proxy),a,r)}function Sn(e,a,r,i){const n=i.includes(".")?Nn(r,i):()=>r[i];if(se(e)){const t=a[e];z(t)&&_a(n,t)}else if(z(e))_a(n,e.bind(r));else if(oe(e))if(B(e))e.forEach(t=>Sn(t,a,r,i));else{const t=z(e.handler)?e.handler.bind(r):a[e.handler];z(t)&&_a(n,t,e)}}function wn(e){const a=e.type,{mixins:r,extends:i}=a,{mixins:n,optionsCache:t,config:{optionMergeStrategies:l}}=e.appContext,s=t.get(a);let m;return s?m=s:!n.length&&!r&&!i?m=a:(m={},n.length&&n.forEach(h=>Xa(m,h,l,!0)),Xa(m,a,l)),t.set(a,m),m}function Xa(e,a,r,i=!1){const{mixins:n,extends:t}=a;t&&Xa(e,t,r,!0),n&&n.forEach(l=>Xa(e,l,r,!0));for(const l in a)if(!(i&&l==="expose")){const s=Mt[l]||r&&r[l];e[l]=s?s(e[l],a[l]):a[l]}return e}const Mt={data:xi,props:na,emits:na,methods:na,computed:na,beforeCreate:ve,created:ve,beforeMount:ve,mounted:ve,beforeUpdate:ve,updated:ve,beforeDestroy:ve,beforeUnmount:ve,destroyed:ve,unmounted:ve,activated:ve,deactivated:ve,errorCaptured:ve,serverPrefetch:ve,components:na,directives:na,watch:vt,provide:xi,inject:ht};function xi(e,a){return a?e?function(){return ge(z(e)?e.call(this,this):e,z(a)?a.call(this,this):a)}:a:e}function ht(e,a){return na(Rr(e),Rr(a))}function Rr(e){if(B(e)){const a={};for(let r=0;r<e.length;r++)a[e[r]]=e[r];return a}return e}function ve(e,a){return e?[...new Set([].concat(e,a))]:a}function na(e,a){return e?ge(ge(Object.create(null),e),a):a}function vt(e,a){if(!e)return a;if(!a)return e;const r=ge(Object.create(null),e);for(const i in a)r[i]=ve(e[i],a[i]);return r}function Ht(e,a,r,i=!1){const n={},t={};Qa(t,ur,1),e.propsDefaults=Object.create(null),Dn(e,a,n,t);for(const l in e.propsOptions[0])l in n||(n[l]=void 0);r?e.props=i?n:Pl(n):e.type.props?e.props=n:e.props=t,e.attrs=t}function bt(e,a,r,i){const{props:n,attrs:t,vnode:{patchFlag:l}}=e,s=K(n),[m]=e.propsOptions;let h=!1;if((i||l>0)&&!(l&16)){if(l&8){const A=e.vnode.dynamicProps;for(let L=0;L<A.length;L++){let f=A[L];if(mr(e.emitsOptions,f))continue;const q=a[f];if(m)if(_(t,f))q!==t[f]&&(t[f]=q,h=!0);else{const W=Na(f);n[W]=Br(m,s,W,q,e,!1)}else q!==t[f]&&(t[f]=q,h=!0)}}}else{Dn(e,a,n,t)&&(h=!0);let A;for(const L in s)(!a||!_(a,L)&&((A=ka(L))===L||!_(a,A)))&&(m?r&&(r[L]!==void 0||r[A]!==void 0)&&(n[L]=Br(m,s,L,void 0,e,!0)):delete n[L]);if(t!==s)for(const L in t)(!a||!_(a,L)&&!0)&&(delete t[L],h=!0)}h&&_e(e,"set","$attrs")}function Dn(e,a,r,i){const[n,t]=e.propsOptions;let l=!1,s;if(a)for(let m in a){if(Wa(m))continue;const h=a[m];let A;n&&_(n,A=Na(m))?!t||!t.includes(A)?r[A]=h:(s||(s={}))[A]=h:mr(e.emitsOptions,m)||(!(m in i)||h!==i[m])&&(i[m]=h,l=!0)}if(t){const m=K(r),h=s||$;for(let A=0;A<t.length;A++){const L=t[A];r[L]=Br(n,m,L,h[L],e,!_(h,L))}}return l}function Br(e,a,r,i,n,t){const l=e[r];if(l!=null){const s=_(l,"default");if(s&&i===void 0){const m=l.default;if(l.type!==Function&&z(m)){const{propsDefaults:h}=n;r in h?i=h[r]:(fa(n),i=h[r]=m.call(null,a),pa())}else i=m}l[0]&&(t&&!s?i=!1:l[1]&&(i===""||i===ka(r))&&(i=!0))}return i}function Pn(e,a,r=!1){const i=a.propsCache,n=i.get(e);if(n)return n;const t=e.props,l={},s=[];let m=!1;if(!z(e)){const A=L=>{m=!0;const[f,q]=Pn(L,a,!0);ge(l,f),q&&s.push(...q)};!r&&a.mixins.length&&a.mixins.forEach(A),e.extends&&A(e.extends),e.mixins&&e.mixins.forEach(A)}if(!t&&!m)return i.set(e,ba),ba;if(B(t))for(let A=0;A<t.length;A++){const L=Na(t[A]);Ni(L)&&(l[L]=$)}else if(t)for(const A in t){const L=Na(A);if(Ni(L)){const f=t[A],q=l[L]=B(f)||z(f)?{type:f}:f;if(q){const W=Ci(Boolean,q.type),j=Ci(String,q.type);q[0]=W>-1,q[1]=j<0||W<j,(W>-1||_(q,"default"))&&s.push(L)}}}const h=[l,s];return i.set(e,h),h}function Ni(e){return e[0]!=="$"}function fi(e){const a=e&&e.toString().match(/^\s*function (\w+)/);return a?a[1]:e===null?"null":""}function ki(e,a){return fi(e)===fi(a)}function Ci(e,a){return B(a)?a.findIndex(r=>ki(r,e)):z(a)&&ki(a,e)?0:-1}const In=e=>e[0]==="_"||e==="$stable",ii=e=>B(e)?e.map(Ue):[Ue(e)],At=(e,a,r)=>{const i=_l((...n)=>ii(a(...n)),r);return i._c=!1,i},En=(e,a,r)=>{const i=e._ctx;for(const n in e){if(In(n))continue;const t=e[n];if(z(t))a[n]=At(n,t,i);else if(t!=null){const l=ii(t);a[n]=()=>l}}},Rn=(e,a)=>{const r=ii(a);e.slots.default=()=>r},xt=(e,a)=>{if(e.vnode.shapeFlag&32){const r=a._;r?(e.slots=K(a),Qa(a,"_",r)):En(a,e.slots={})}else e.slots={},a&&Rn(e,a);Qa(e.slots,ur,1)},Nt=(e,a,r)=>{const{vnode:i,slots:n}=e;let t=!0,l=$;if(i.shapeFlag&32){const s=a._;s?r&&s===1?t=!1:(ge(n,a),!r&&s===1&&delete n._):(t=!a.$stable,En(a,n)),l=a}else a&&(Rn(e,a),l={default:1});if(t)for(const s in n)!In(s)&&!(s in l)&&delete n[s]};function ea(e,a){const r=we;if(r===null)return e;const i=gr(r)||r.proxy,n=e.dirs||(e.dirs=[]);for(let t=0;t<a.length;t++){let[l,s,m,h=$]=a[t];z(l)&&(l={mounted:l,updated:l}),l.deep&&sa(s),n.push({dir:l,instance:i,value:s,oldValue:void 0,arg:m,modifiers:h})}return e}function aa(e,a,r,i){const n=e.dirs,t=a&&a.dirs;for(let l=0;l<n.length;l++){const s=n[l];t&&(s.oldValue=t[l].value);let m=s.dir[i];m&&(Ca(),Ce(m,r,8,[e.el,s,e,a]),ya())}}function Bn(){return{app:null,config:{isNativeTag:$n,performance:!1,globalProperties:{},optionMergeStrategies:{},errorHandler:void 0,warnHandler:void 0,compilerOptions:{}},mixins:[],components:{},directives:{},provides:Object.create(null),optionsCache:new WeakMap,propsCache:new WeakMap,emitsCache:new WeakMap}}let ft=0;function kt(e,a){return function(i,n=null){z(i)||(i=Object.assign({},i)),n!=null&&!oe(n)&&(n=null);const t=Bn(),l=new Set;let s=!1;const m=t.app={_uid:ft++,_component:i,_props:n,_container:null,_context:t,_instance:null,version:Jt,get config(){return t.config},set config(h){},use(h,...A){return l.has(h)||(h&&z(h.install)?(l.add(h),h.install(m,...A)):z(h)&&(l.add(h),h(m,...A))),m},mixin(h){return t.mixins.includes(h)||t.mixins.push(h),m},component(h,A){return A?(t.components[h]=A,m):t.components[h]},directive(h,A){return A?(t.directives[h]=A,m):t.directives[h]},mount(h,A,L){if(!s){const f=je(i,n);return f.appContext=t,A&&a?a(f,h):e(f,h,L),s=!0,m._container=h,h.__vue_app__=m,gr(f.component)||f.component.proxy}},unmount(){s&&(e(null,m._container),delete m._container.__vue_app__)},provide(h,A){return t.provides[h]=A,m}};return m}}function qr(e,a,r,i,n=!1){if(B(e)){e.forEach((f,q)=>qr(f,a&&(B(a)?a[q]:a),r,i,n));return}if(Ir(i)&&!n)return;const t=i.shapeFlag&4?gr(i.component)||i.component.proxy:i.el,l=n?null:t,{i:s,r:m}=e,h=a&&a.r,A=s.refs===$?s.refs={}:s.refs,L=s.setupState;if(h!=null&&h!==m&&(se(h)?(A[h]=null,_(L,h)&&(L[h]=null)):ue(h)&&(h.value=null)),z(m))$e(m,s,12,[l,A]);else{const f=se(m),q=ue(m);if(f||q){const W=()=>{if(e.f){const j=f?A[m]:m.value;n?B(j)&&jr(j,t):B(j)?j.includes(t)||j.push(t):f?(A[m]=[t],_(L,m)&&(L[m]=A[m])):(m.value=[t],e.k&&(A[e.k]=m.value))}else f?(A[m]=l,_(L,m)&&(L[m]=l)):ue(m)&&(m.value=l,e.k&&(A[e.k]=l))};l?(W.id=-1,He(W,r)):W()}}}const He=Xl;function Ct(e){return yt(e)}function yt(e,a){const r=nl();r.__VUE__=!0;const{insert:i,remove:n,patchProp:t,createElement:l,createText:s,createComment:m,setText:h,setElementText:A,parentNode:L,nextSibling:f,setScopeId:q=De,cloneNode:W,insertStaticContent:j}=e,U=(o,c,M,v=null,H=null,x=null,y=!1,N=null,k=!!c.dynamicChildren)=>{if(o===c)return;o&&!la(o,c)&&(v=Ae(o),te(o,H,x,!0),o=null),c.patchFlag===-2&&(k=!1,c.dynamicChildren=null);const{type:b,ref:d,shapeFlag:w}=c;switch(b){case ni:V(o,c,M,v);break;case Pe:Me(o,c,M,v);break;case br:o==null&&le(c,M,v,y);break;case be:S(o,c,M,v,H,x,y,N,k);break;default:w&1?Ie(o,c,M,v,H,x,y,N,k):w&6?Z(o,c,M,v,H,x,y,N,k):(w&64||w&128)&&b.process(o,c,M,v,H,x,y,N,k,ze)}d!=null&&H&&qr(d,o&&o.ref,x,c||o,!c)},V=(o,c,M,v)=>{if(o==null)i(c.el=s(c.children),M,v);else{const H=c.el=o.el;c.children!==o.children&&h(H,c.children)}},Me=(o,c,M,v)=>{o==null?i(c.el=m(c.children||""),M,v):c.el=o.el},le=(o,c,M,v)=>{[o.el,o.anchor]=j(o.children,c,M,v,o.el,o.anchor)},Y=({el:o,anchor:c},M,v)=>{let H;for(;o&&o!==c;)H=f(o),i(o,M,v),o=H;i(c,M,v)},ce=({el:o,anchor:c})=>{let M;for(;o&&o!==c;)M=f(o),n(o),o=M;n(c)},Ie=(o,c,M,v,H,x,y,N,k)=>{y=y||c.type==="svg",o==null?J(c,M,v,H,x,y,N,k):u(o,c,H,x,y,N,k)},J=(o,c,M,v,H,x,y,N)=>{let k,b;const{type:d,props:w,shapeFlag:D,transition:E,patchFlag:O,dirs:ae}=o;if(o.el&&W!==void 0&&O===-1)k=o.el=W(o.el);else{if(k=o.el=l(o.type,x,w&&w.is,w),D&8?A(k,o.children):D&16&&p(o.children,k,null,v,H,x&&d!=="foreignObject",y,N),ae&&aa(o,null,v,"created"),w){for(const ee in w)ee!=="value"&&!Wa(ee)&&t(k,ee,null,w[ee],x,o.children,v,H,pe);"value"in w&&t(k,"value",null,w.value),(b=w.onVnodeBeforeMount)&&qe(b,v,o)}re(k,o,o.scopeId,y,v)}ae&&aa(o,null,v,"beforeMount");const X=(!H||H&&!H.pendingBranch)&&E&&!E.persisted;X&&E.beforeEnter(k),i(k,c,M),((b=w&&w.onVnodeMounted)||X||ae)&&He(()=>{b&&qe(b,v,o),X&&E.enter(k),ae&&aa(o,null,v,"mounted")},H)},re=(o,c,M,v,H)=>{if(M&&q(o,M),v)for(let x=0;x<v.length;x++)q(o,v[x]);if(H){let x=H.subTree;if(c===x){const y=H.vnode;re(o,y,y.scopeId,y.slotScopeIds,H.parent)}}},p=(o,c,M,v,H,x,y,N,k=0)=>{for(let b=k;b<o.length;b++){const d=o[b]=N?Ye(o[b]):Ue(o[b]);U(null,d,c,M,v,H,x,y,N)}},u=(o,c,M,v,H,x,y)=>{const N=c.el=o.el;let{patchFlag:k,dynamicChildren:b,dirs:d}=c;k|=o.patchFlag&16;const w=o.props||$,D=c.props||$;let E;M&&ra(M,!1),(E=D.onVnodeBeforeUpdate)&&qe(E,M,c,o),d&&aa(c,o,M,"beforeUpdate"),M&&ra(M,!0);const O=H&&c.type!=="foreignObject";if(b?g(o.dynamicChildren,b,N,M,v,O,x):y||I(o,c,N,null,M,v,O,x,!1),k>0){if(k&16)C(N,c,w,D,M,v,H);else if(k&2&&w.class!==D.class&&t(N,"class",null,D.class,H),k&4&&t(N,"style",w.style,D.style,H),k&8){const ae=c.dynamicProps;for(let X=0;X<ae.length;X++){const ee=ae[X],Le=w[ee],Ma=D[ee];(Ma!==Le||ee==="value")&&t(N,ee,Le,Ma,H,o.children,M,v,pe)}}k&1&&o.children!==c.children&&A(N,c.children)}else!y&&b==null&&C(N,c,w,D,M,v,H);((E=D.onVnodeUpdated)||d)&&He(()=>{E&&qe(E,M,c,o),d&&aa(c,o,M,"updated")},v)},g=(o,c,M,v,H,x,y)=>{for(let N=0;N<c.length;N++){const k=o[N],b=c[N],d=k.el&&(k.type===be||!la(k,b)||k.shapeFlag&70)?L(k.el):M;U(k,b,d,null,v,H,x,y,!0)}},C=(o,c,M,v,H,x,y)=>{if(M!==v){for(const N in v){if(Wa(N))continue;const k=v[N],b=M[N];k!==b&&N!=="value"&&t(o,N,b,k,y,c.children,H,x,pe)}if(M!==$)for(const N in M)!Wa(N)&&!(N in v)&&t(o,N,M[N],null,y,c.children,H,x,pe);"value"in v&&t(o,"value",M.value,v.value)}},S=(o,c,M,v,H,x,y,N,k)=>{const b=c.el=o?o.el:s(""),d=c.anchor=o?o.anchor:s("");let{patchFlag:w,dynamicChildren:D,slotScopeIds:E}=c;E&&(N=N?N.concat(E):E),o==null?(i(b,M,v),i(d,M,v),p(c.children,M,d,H,x,y,N,k)):w>0&&w&64&&D&&o.dynamicChildren?(g(o.dynamicChildren,D,M,H,x,y,N),(c.key!=null||H&&c===H.subTree)&&qn(o,c,!0)):I(o,c,M,d,H,x,y,N,k)},Z=(o,c,M,v,H,x,y,N,k)=>{c.slotScopeIds=N,o==null?c.shapeFlag&512?H.ctx.activate(c,M,v,y,k):ne(c,M,v,H,x,y,k):R(o,c,k)},ne=(o,c,M,v,H,x,y)=>{const N=o.component=Ot(o,v,H);if(pr(o)&&(N.ctx.renderer=ze),Ft(N),N.asyncDep){if(H&&H.registerDep(N,T),!o.el){const k=N.subTree=je(Pe);Me(null,k,c,M)}return}T(N,o,c,M,H,x,y)},R=(o,c,M)=>{const v=c.component=o.component;if(Ql(o,c,M))if(v.asyncDep&&!v.asyncResolved){P(v,c,M);return}else v.next=c,zl(v.update),v.update();else c.component=o.component,c.el=o.el,v.vnode=c},T=(o,c,M,v,H,x,y)=>{const N=()=>{if(o.isMounted){let{next:d,bu:w,u:D,parent:E,vnode:O}=o,ae=d,X;ra(o,!1),d?(d.el=O.el,P(o,d,y)):d=O,w&&ja(w),(X=d.props&&d.props.onVnodeBeforeUpdate)&&qe(X,E,d,O),ra(o,!0);const ee=hr(o),Le=o.subTree;o.subTree=ee,U(Le,ee,L(Le.el),Ae(Le),o,H,x),d.el=ee.el,ae===null&&Kl(o,ee.el),D&&He(D,H),(X=d.props&&d.props.onVnodeUpdated)&&He(()=>qe(X,E,d,O),H)}else{let d;const{el:w,props:D}=c,{bm:E,m:O,parent:ae}=o,X=Ir(c);if(ra(o,!1),E&&ja(E),!X&&(d=D&&D.onVnodeBeforeMount)&&qe(d,ae,c),ra(o,!0),w&&Fe){const ee=()=>{o.subTree=hr(o),Fe(w,o.subTree,o,H,null)};X?c.type.__asyncLoader().then(()=>!o.isUnmounted&&ee()):ee()}else{const ee=o.subTree=hr(o);U(null,ee,M,v,o,H,x),c.el=ee.el}if(O&&He(O,H),!X&&(d=D&&D.onVnodeMounted)){const ee=c;He(()=>qe(d,ae,ee),H)}c.shapeFlag&256&&o.a&&He(o.a,H),o.isMounted=!0,c=M=v=null}},k=o.effect=new Qr(N,()=>gn(o.update),o.scope),b=o.update=k.run.bind(k);b.id=o.uid,ra(o,!0),b()},P=(o,c,M)=>{c.component=o;const v=o.vnode.props;o.vnode=c,o.next=null,bt(o,c.props,v,M),Nt(o,c.children,M),Ca(),ri(void 0,o.update),ya()},I=(o,c,M,v,H,x,y,N,k=!1)=>{const b=o&&o.children,d=o?o.shapeFlag:0,w=c.children,{patchFlag:D,shapeFlag:E}=c;if(D>0){if(D&128){F(b,w,M,v,H,x,y,N,k);return}else if(D&256){Ee(b,w,M,v,H,x,y,N,k);return}}E&8?(d&16&&pe(b,H,x),w!==b&&A(M,w)):d&16?E&16?F(b,w,M,v,H,x,y,N,k):pe(b,H,x,!0):(d&8&&A(M,""),E&16&&p(w,M,v,H,x,y,N,k))},Ee=(o,c,M,v,H,x,y,N,k)=>{o=o||ba,c=c||ba;const b=o.length,d=c.length,w=Math.min(b,d);let D;for(D=0;D<w;D++){const E=c[D]=k?Ye(c[D]):Ue(c[D]);U(o[D],E,M,null,H,x,y,N,k)}b>d?pe(o,H,x,!0,!1,w):p(c,M,v,H,x,y,N,k,w)},F=(o,c,M,v,H,x,y,N,k)=>{let b=0;const d=c.length;let w=o.length-1,D=d-1;for(;b<=w&&b<=D;){const E=o[b],O=c[b]=k?Ye(c[b]):Ue(c[b]);if(la(E,O))U(E,O,M,null,H,x,y,N,k);else break;b++}for(;b<=w&&b<=D;){const E=o[w],O=c[D]=k?Ye(c[D]):Ue(c[D]);if(la(E,O))U(E,O,M,null,H,x,y,N,k);else break;w--,D--}if(b>w){if(b<=D){const E=D+1,O=E<d?c[E].el:v;for(;b<=D;)U(null,c[b]=k?Ye(c[b]):Ue(c[b]),M,O,H,x,y,N,k),b++}}else if(b>D)for(;b<=w;)te(o[b],H,x,!0),b++;else{const E=b,O=b,ae=new Map;for(b=O;b<=D;b++){const xe=c[b]=k?Ye(c[b]):Ue(c[b]);xe.key!=null&&ae.set(xe.key,b)}let X,ee=0;const Le=D-O+1;let Ma=!1,ti=0;const La=new Array(Le);for(b=0;b<Le;b++)La[b]=0;for(b=E;b<=w;b++){const xe=o[b];if(ee>=Le){te(xe,H,x,!0);continue}let Be;if(xe.key!=null)Be=ae.get(xe.key);else for(X=O;X<=D;X++)if(La[X-O]===0&&la(xe,c[X])){Be=X;break}Be===void 0?te(xe,H,x,!0):(La[Be-O]=b+1,Be>=ti?ti=Be:Ma=!0,U(xe,c[Be],M,null,H,x,y,N,k),ee++)}const oi=Ma?Lt(La):ba;for(X=oi.length-1,b=Le-1;b>=0;b--){const xe=O+b,Be=c[xe],si=xe+1<d?c[xe+1].el:v;La[b]===0?U(null,Be,M,si,H,x,y,N,k):Ma&&(X<0||b!==oi[X]?ie(Be,M,si,2):X--)}}},ie=(o,c,M,v,H=null)=>{const{el:x,type:y,transition:N,children:k,shapeFlag:b}=o;if(b&6){ie(o.component.subTree,c,M,v);return}if(b&128){o.suspense.move(c,M,v);return}if(b&64){y.move(o,c,M,ze);return}if(y===be){i(x,c,M);for(let w=0;w<k.length;w++)ie(k[w],c,M,v);i(o.anchor,c,M);return}if(y===br){Y(o,c,M);return}if(v!==2&&b&1&&N)if(v===0)N.beforeEnter(x),i(x,c,M),He(()=>N.enter(x),H);else{const{leave:w,delayLeave:D,afterLeave:E}=N,O=()=>i(x,c,M),ae=()=>{w(x,()=>{O(),E&&E()})};D?D(x,O,ae):ae()}else i(x,c,M)},te=(o,c,M,v=!1,H=!1)=>{const{type:x,props:y,ref:N,children:k,dynamicChildren:b,shapeFlag:d,patchFlag:w,dirs:D}=o;if(N!=null&&qr(N,null,M,o,!0),d&256){c.ctx.deactivate(o);return}const E=d&1&&D,O=!Ir(o);let ae;if(O&&(ae=y&&y.onVnodeBeforeUnmount)&&qe(ae,c,o),d&6)ye(o.component,M,v);else{if(d&128){o.suspense.unmount(M,v);return}E&&aa(o,null,c,"beforeUnmount"),d&64?o.type.remove(o,c,M,H,ze,v):b&&(x!==be||w>0&&w&64)?pe(b,c,M,!1,!0):(x===be&&w&384||!H&&d&16)&&pe(k,c,M),v&&Oe(o)}(O&&(ae=y&&y.onVnodeUnmounted)||E)&&He(()=>{ae&&qe(ae,c,o),E&&aa(o,null,c,"unmounted")},M)},Oe=o=>{const{type:c,el:M,anchor:v,transition:H}=o;if(c===be){Re(M,v);return}if(c===br){ce(o);return}const x=()=>{n(M),H&&!H.persisted&&H.afterLeave&&H.afterLeave()};if(o.shapeFlag&1&&H&&!H.persisted){const{leave:y,delayLeave:N}=H,k=()=>y(M,x);N?N(o.el,x,k):k()}else x()},Re=(o,c)=>{let M;for(;o!==c;)M=f(o),n(o),o=M;n(c)},ye=(o,c,M)=>{const{bum:v,scope:H,update:x,subTree:y,um:N}=o;v&&ja(v),H.stop(),x&&(x.active=!1,te(y,o,c,M)),N&&He(N,c),He(()=>{o.isUnmounted=!0},c),c&&c.pendingBranch&&!c.isUnmounted&&o.asyncDep&&!o.asyncResolved&&o.suspenseId===c.pendingId&&(c.deps--,c.deps===0&&c.resolve())},pe=(o,c,M,v=!1,H=!1,x=0)=>{for(let y=x;y<o.length;y++)te(o[y],c,M,v,H)},Ae=o=>o.shapeFlag&6?Ae(o.component.subTree):o.shapeFlag&128?o.suspense.next():f(o.anchor||o.el),ua=(o,c,M)=>{o==null?c._vnode&&te(c._vnode,null,null,!0):U(c._vnode||null,o,c,null,null,null,M),vn(),c._vnode=o},ze={p:U,um:te,m:ie,r:Oe,mt:ne,mc:p,pc:I,pbc:g,n:Ae,o:e};let ga,Fe;return a&&([ga,Fe]=a(ze)),{render:ua,hydrate:ga,createApp:kt(ua,ga)}}function ra({effect:e,update:a},r){e.allowRecurse=a.allowRecurse=r}function qn(e,a,r=!1){const i=e.children,n=a.children;if(B(i)&&B(n))for(let t=0;t<i.length;t++){const l=i[t];let s=n[t];s.shapeFlag&1&&!s.dynamicChildren&&((s.patchFlag<=0||s.patchFlag===32)&&(s=n[t]=Ye(n[t]),s.el=l.el),r||qn(l,s))}}function Lt(e){const a=e.slice(),r=[0];let i,n,t,l,s;const m=e.length;for(i=0;i<m;i++){const h=e[i];if(h!==0){if(n=r[r.length-1],e[n]<h){a[i]=n,r.push(i);continue}for(t=0,l=r.length-1;t<l;)s=t+l>>1,e[r[s]]<h?t=s+1:l=s;h<e[r[t]]&&(t>0&&(a[i]=r[t-1]),r[t]=i)}}for(t=r.length,l=r[t-1];t-- >0;)r[t]=l,l=a[l];return r}const Tt=e=>e.__isTeleport,St=Symbol(),be=Symbol(void 0),ni=Symbol(void 0),Pe=Symbol(void 0),br=Symbol(void 0),Ia=[];let ma=null;function de(e=!1){Ia.push(ma=e?null:[])}function wt(){Ia.pop(),ma=Ia[Ia.length-1]||null}let $a=1;function yi(e){$a+=e}function Gn(e){return e.dynamicChildren=$a>0?ma||ba:null,wt(),$a>0&&ma&&ma.push(e),e}function he(e,a,r,i,n,t){return Gn(G(e,a,r,i,n,t,!0))}function Dt(e,a,r,i,n){return Gn(je(e,a,r,i,n,!0))}function Pt(e){return e?e.__v_isVNode===!0:!1}function la(e,a){return e.type===a.type&&e.key===a.key}const ur="__vInternal",Un=({key:e})=>e!=null?e:null,Va=({ref:e,ref_key:a,ref_for:r})=>e!=null?se(e)||ue(e)||z(e)?{i:we,r:e,k:a,f:!!r}:e:null;function G(e,a=null,r=null,i=0,n=null,t=e===be?0:1,l=!1,s=!1){const m={__v_isVNode:!0,__v_skip:!0,type:e,props:a,key:a&&Un(a),ref:a&&Va(a),scopeId:An,slotScopeIds:null,children:r,component:null,suspense:null,ssContent:null,ssFallback:null,dirs:null,transition:null,el:null,anchor:null,target:null,targetAnchor:null,staticCount:0,shapeFlag:t,patchFlag:i,dynamicProps:n,dynamicChildren:null,appContext:null};return s?(li(m,r),t&128&&e.normalize(m)):r&&(m.shapeFlag|=se(r)?8:16),$a>0&&!l&&ma&&(m.patchFlag>0||t&6)&&m.patchFlag!==32&&ma.push(m),m}const je=It;function It(e,a=null,r=null,i=0,n=null,t=!1){if((!e||e===St)&&(e=Pe),Pt(e)){const s=da(e,a,!0);return r&&li(s,r),s}if(Vt(e)&&(e=e.__vccOpts),a){a=Et(a);let{class:s,style:m}=a;s&&!se(s)&&(a.class=Fr(s)),oe(m)&&(mn(m)&&!B(m)&&(m=ge({},m)),a.style=ar(m))}const l=se(e)?1:Yl(e)?128:Tt(e)?64:oe(e)?4:z(e)?2:0;return G(e,a,r,i,n,l,t,!0)}function Et(e){return e?mn(e)||ur in e?ge({},e):e:null}function da(e,a,r=!1){const{props:i,ref:n,patchFlag:t,children:l}=e,s=a?Bt(i||{},a):i;return{__v_isVNode:!0,__v_skip:!0,type:e.type,props:s,key:s&&Un(s),ref:a&&a.ref?r&&n?B(n)?n.concat(Va(a)):[n,Va(a)]:Va(a):n,scopeId:e.scopeId,slotScopeIds:e.slotScopeIds,children:l,target:e.target,targetAnchor:e.targetAnchor,staticCount:e.staticCount,shapeFlag:e.shapeFlag,patchFlag:a&&e.type!==be?t===-1?16:t|16:t,dynamicProps:e.dynamicProps,dynamicChildren:e.dynamicChildren,appContext:e.appContext,dirs:e.dirs,transition:e.transition,component:e.component,suspense:e.suspense,ssContent:e.ssContent&&da(e.ssContent),ssFallback:e.ssFallback&&da(e.ssFallback),el:e.el,anchor:e.anchor}}function Rt(e=" ",a=0){return je(ni,null,e,a)}function Fa(e="",a=!1){return a?(de(),Dt(Pe,null,e)):je(Pe,null,e)}function Ue(e){return e==null||typeof e=="boolean"?je(Pe):B(e)?je(be,null,e.slice()):typeof e=="object"?Ye(e):je(ni,null,String(e))}function Ye(e){return e.el===null||e.memo?e:da(e)}function li(e,a){let r=0;const{shapeFlag:i}=e;if(a==null)a=null;else if(B(a))r=16;else if(typeof a=="object")if(i&65){const n=a.default;n&&(n._c&&(n._d=!1),li(e,n()),n._c&&(n._d=!0));return}else{r=32;const n=a._;!n&&!(ur in a)?a._ctx=we:n===3&&we&&(we.slots._===1?a._=1:(a._=2,e.patchFlag|=1024))}else z(a)?(a={default:a,_ctx:we},r=32):(a=String(a),i&64?(r=16,a=[Rt(a)]):r=8);e.children=a,e.shapeFlag|=r}function Bt(...e){const a={};for(let r=0;r<e.length;r++){const i=e[r];for(const n in i)if(n==="class")a.class!==i.class&&(a.class=Fr([a.class,i.class]));else if(n==="style")a.style=ar([a.style,i.style]);else if(ir(n)){const t=a[n],l=i[n];l&&t!==l&&!(B(t)&&t.includes(l))&&(a[n]=t?[].concat(t,l):l)}else n!==""&&(a[n]=i[n])}return a}function qe(e,a,r,i=null){Ce(e,a,7,[r,i])}function Ar(e,a,r,i){let n;const t=r&&r[i];if(B(e)||se(e)){n=new Array(e.length);for(let l=0,s=e.length;l<s;l++)n[l]=a(e[l],l,void 0,t&&t[l])}else if(typeof e=="number"){n=new Array(e);for(let l=0;l<e;l++)n[l]=a(l+1,l,void 0,t&&t[l])}else if(oe(e))if(e[Symbol.iterator])n=Array.from(e,(l,s)=>a(l,s,void 0,t&&t[s]));else{const l=Object.keys(e);n=new Array(l.length);for(let s=0,m=l.length;s<m;s++){const h=l[s];n[s]=a(e[h],h,s,t&&t[s])}}else n=[];return r&&(r[i]=n),n}const Gr=e=>e?On(e)?gr(e)||e.proxy:Gr(e.parent):null,Za=ge(Object.create(null),{$:e=>e,$el:e=>e.vnode.el,$data:e=>e.data,$props:e=>e.props,$attrs:e=>e.attrs,$slots:e=>e.slots,$refs:e=>e.refs,$parent:e=>Gr(e.parent),$root:e=>Gr(e.root),$emit:e=>e.emit,$options:e=>wn(e),$forceUpdate:e=>()=>gn(e.update),$nextTick:e=>Ul.bind(e.proxy),$watch:e=>Zl.bind(e)}),qt={get({_:e},a){const{ctx:r,setupState:i,data:n,props:t,accessCache:l,type:s,appContext:m}=e;let h;if(a[0]!=="$"){const q=l[a];if(q!==void 0)switch(q){case 1:return i[a];case 2:return n[a];case 4:return r[a];case 3:return t[a]}else{if(i!==$&&_(i,a))return l[a]=1,i[a];if(n!==$&&_(n,a))return l[a]=2,n[a];if((h=e.propsOptions[0])&&_(h,a))return l[a]=3,t[a];if(r!==$&&_(r,a))return l[a]=4,r[a];Er&&(l[a]=0)}}const A=Za[a];let L,f;if(A)return a==="$attrs"&&fe(e,"get",a),A(e);if((L=s.__cssModules)&&(L=L[a]))return L;if(r!==$&&_(r,a))return l[a]=4,r[a];if(f=m.config.globalProperties,_(f,a))return f[a]},set({_:e},a,r){const{data:i,setupState:n,ctx:t}=e;return n!==$&&_(n,a)?(n[a]=r,!0):i!==$&&_(i,a)?(i[a]=r,!0):_(e.props,a)||a[0]==="$"&&a.slice(1)in e?!1:(t[a]=r,!0)},has({_:{data:e,setupState:a,accessCache:r,ctx:i,appContext:n,propsOptions:t}},l){let s;return!!r[l]||e!==$&&_(e,l)||a!==$&&_(a,l)||(s=t[0])&&_(s,l)||_(i,l)||_(Za,l)||_(n.config.globalProperties,l)},defineProperty(e,a,r){return r.get!=null?e._.accessCache[a]=0:_(r,"value")&&this.set(e,a,r.value,null),Reflect.defineProperty(e,a,r)}},Gt=Bn();let Ut=0;function Ot(e,a,r){const i=e.type,n=(a?a.appContext:e.appContext)||Gt,t={uid:Ut++,vnode:e,type:i,parent:a,appContext:n,root:null,next:null,subTree:null,effect:null,update:null,scope:new ll(!0),render:null,proxy:null,exposed:null,exposeProxy:null,withProxy:null,provides:a?a.provides:Object.create(n.provides),accessCache:null,renderCache:[],components:null,directives:null,propsOptions:Pn(i,n),emitsOptions:bn(i,n),emit:null,emitted:null,propsDefaults:$,inheritAttrs:i.inheritAttrs,ctx:$,data:$,props:$,attrs:$,slots:$,refs:$,setupState:$,setupContext:null,suspense:r,suspenseId:r?r.pendingId:0,asyncDep:null,asyncResolved:!1,isMounted:!1,isUnmounted:!1,isDeactivated:!1,bc:null,c:null,bm:null,m:null,bu:null,u:null,um:null,bum:null,da:null,a:null,rtg:null,rtc:null,ec:null,sp:null};return t.ctx={_:t},t.root=a?a.root:t,t.emit=jl.bind(null,t),e.ce&&e.ce(t),t}let me=null;const zt=()=>me||we,fa=e=>{me=e,e.scope.on()},pa=()=>{me&&me.scope.off(),me=null};function On(e){return e.vnode.shapeFlag&4}let Ba=!1;function Ft(e,a=!1){Ba=a;const{props:r,children:i}=e.vnode,n=On(e);Ht(e,r,n,a),xt(e,i);const t=n?Wt(e,a):void 0;return Ba=!1,t}function Wt(e,a){const r=e.type;e.accessCache=Object.create(null),e.proxy=pn(new Proxy(e.ctx,qt));const{setup:i}=r;if(i){const n=e.setupContext=i.length>1?_t(e):null;fa(e),Ca();const t=$e(i,e,0,[e.props,n]);if(ya(),pa(),Ji(t)){if(t.then(pa,pa),a)return t.then(l=>{Li(e,l,a)}).catch(l=>{cr(l,e,0)});e.asyncDep=t}else Li(e,t,a)}else zn(e,a)}function Li(e,a,r){z(a)?e.type.__ssrInlineRender?e.ssrRender=a:e.render=a:oe(a)&&(e.setupState=dn(a)),zn(e,r)}let Ti;function zn(e,a,r){const i=e.type;if(!e.render){if(!a&&Ti&&!i.render){const n=i.template;if(n){const{isCustomElement:t,compilerOptions:l}=e.appContext.config,{delimiters:s,compilerOptions:m}=i,h=ge(ge({isCustomElement:t,delimiters:s},l),m);i.render=Ti(n,h)}}e.render=i.render||De}fa(e),Ca(),ut(e),ya(),pa()}function jt(e){return new Proxy(e.attrs,{get(a,r){return fe(e,"get","$attrs"),a[r]}})}function _t(e){const a=i=>{e.exposed=i||{}};let r;return{get attrs(){return r||(r=jt(e))},slots:e.slots,emit:e.emit,expose:a}}function gr(e){if(e.exposed)return e.exposeProxy||(e.exposeProxy=new Proxy(dn(pn(e.exposed)),{get(a,r){if(r in a)return a[r];if(r in Za)return Za[r](e)}}))}function Vt(e){return z(e)&&"__vccOpts"in e}const Fn=(e,a)=>ql(e,a,Ba),Jt="3.2.33",Qt="http://www.w3.org/2000/svg",ta=typeof document!="undefined"?document:null,Si=ta&&ta.createElement("template"),Kt={insert:(e,a,r)=>{a.insertBefore(e,r||null)},remove:e=>{const a=e.parentNode;a&&a.removeChild(e)},createElement:(e,a,r,i)=>{const n=a?ta.createElementNS(Qt,e):ta.createElement(e,r?{is:r}:void 0);return e==="select"&&i&&i.multiple!=null&&n.setAttribute("multiple",i.multiple),n},createText:e=>ta.createTextNode(e),createComment:e=>ta.createComment(e),setText:(e,a)=>{e.nodeValue=a},setElementText:(e,a)=>{e.textContent=a},parentNode:e=>e.parentNode,nextSibling:e=>e.nextSibling,querySelector:e=>ta.querySelector(e),setScopeId(e,a){e.setAttribute(a,"")},cloneNode(e){const a=e.cloneNode(!0);return"_value"in e&&(a._value=e._value),a},insertStaticContent(e,a,r,i,n,t){const l=r?r.previousSibling:a.lastChild;if(n&&(n===t||n.nextSibling))for(;a.insertBefore(n.cloneNode(!0),r),!(n===t||!(n=n.nextSibling)););else{Si.innerHTML=i?`<svg>${e}</svg>`:e;const s=Si.content;if(i){const m=s.firstChild;for(;m.firstChild;)s.appendChild(m.firstChild);s.removeChild(m)}a.insertBefore(s,r)}return[l?l.nextSibling:a.firstChild,r?r.previousSibling:a.lastChild]}};function Yt(e,a,r){const i=e._vtc;i&&(a=(a?[a,...i]:[...i]).join(" ")),a==null?e.removeAttribute("class"):r?e.setAttribute("class",a):e.className=a}function Xt(e,a,r){const i=e.style,n=se(r);if(r&&!n){for(const t in r)Ur(i,t,r[t]);if(a&&!se(a))for(const t in a)r[t]==null&&Ur(i,t,"")}else{const t=i.display;n?a!==r&&(i.cssText=r):a&&e.removeAttribute("style"),"_vod"in e&&(i.display=t)}}const wi=/\s*!important$/;function Ur(e,a,r){if(B(r))r.forEach(i=>Ur(e,a,i));else if(r==null&&(r=""),a.startsWith("--"))e.setProperty(a,r);else{const i=$t(e,a);wi.test(r)?e.setProperty(ka(i),r.replace(wi,""),"important"):e[i]=r}}const Di=["Webkit","Moz","ms"],xr={};function $t(e,a){const r=xr[a];if(r)return r;let i=Na(a);if(i!=="filter"&&i in e)return xr[a]=i;i=Yi(i);for(let n=0;n<Di.length;n++){const t=Di[n]+i;if(t in e)return xr[a]=t}return a}const Pi="http://www.w3.org/1999/xlink";function Zt(e,a,r,i,n){if(i&&a.startsWith("xlink:"))r==null?e.removeAttributeNS(Pi,a.slice(6,a.length)):e.setAttributeNS(Pi,a,r);else{const t=Jn(a);r==null||t&&!ji(r)?e.removeAttribute(a):e.setAttribute(a,t?"":r)}}function eo(e,a,r,i,n,t,l){if(a==="innerHTML"||a==="textContent"){i&&l(i,n,t),e[a]=r==null?"":r;return}if(a==="value"&&e.tagName!=="PROGRESS"&&!e.tagName.includes("-")){e._value=r;const m=r==null?"":r;(e.value!==m||e.tagName==="OPTION")&&(e.value=m),r==null&&e.removeAttribute(a);return}let s=!1;if(r===""||r==null){const m=typeof e[a];m==="boolean"?r=ji(r):r==null&&m==="string"?(r="",s=!0):m==="number"&&(r=0,s=!0)}try{e[a]=r}catch{}s&&e.removeAttribute(a)}const[Wn,ao]=(()=>{let e=Date.now,a=!1;if(typeof window!="undefined"){Date.now()>document.createEvent("Event").timeStamp&&(e=()=>performance.now());const r=navigator.userAgent.match(/firefox\/(\d+)/i);a=!!(r&&Number(r[1])<=53)}return[e,a]})();let Or=0;const ro=Promise.resolve(),io=()=>{Or=0},no=()=>Or||(ro.then(io),Or=Wn());function oa(e,a,r,i){e.addEventListener(a,r,i)}function lo(e,a,r,i){e.removeEventListener(a,r,i)}function to(e,a,r,i,n=null){const t=e._vei||(e._vei={}),l=t[a];if(i&&l)l.value=i;else{const[s,m]=oo(a);if(i){const h=t[a]=so(i,n);oa(e,s,h,m)}else l&&(lo(e,s,l,m),t[a]=void 0)}}const Ii=/(?:Once|Passive|Capture)$/;function oo(e){let a;if(Ii.test(e)){a={};let r;for(;r=e.match(Ii);)e=e.slice(0,e.length-r[0].length),a[r[0].toLowerCase()]=!0}return[ka(e.slice(2)),a]}function so(e,a){const r=i=>{const n=i.timeStamp||Wn();(ao||n>=r.attached-1)&&Ce(co(i,r.value),a,5,[i])};return r.value=e,r.attached=no(),r}function co(e,a){if(B(a)){const r=e.stopImmediatePropagation;return e.stopImmediatePropagation=()=>{r.call(e),e._stopped=!0},a.map(i=>n=>!n._stopped&&i&&i(n))}else return a}const Ei=/^on[a-z]/,mo=(e,a,r,i,n=!1,t,l,s,m)=>{a==="class"?Yt(e,i,n):a==="style"?Xt(e,r,i):ir(a)?Wr(a)||to(e,a,r,i,l):(a[0]==="."?(a=a.slice(1),!0):a[0]==="^"?(a=a.slice(1),!1):po(e,a,i,n))?eo(e,a,i,t,l,s,m):(a==="true-value"?e._trueValue=i:a==="false-value"&&(e._falseValue=i),Zt(e,a,i,n))};function po(e,a,r,i){return i?!!(a==="innerHTML"||a==="textContent"||a in e&&Ei.test(a)&&z(r)):a==="spellcheck"||a==="draggable"||a==="translate"||a==="form"||a==="list"&&e.tagName==="INPUT"||a==="type"&&e.tagName==="TEXTAREA"||Ei.test(a)&&se(r)?!1:a in e}const uo={name:String,type:String,css:{type:Boolean,default:!0},duration:[String,Number,Object],enterFromClass:String,enterActiveClass:String,enterToClass:String,appearFromClass:String,appearActiveClass:String,appearToClass:String,leaveFromClass:String,leaveActiveClass:String,leaveToClass:String};rt.props;const er=e=>{const a=e.props["onUpdate:modelValue"];return B(a)?r=>ja(a,r):a};function go(e){e.target.composing=!0}function Ri(e){const a=e.target;a.composing&&(a.composing=!1,Mo(a,"input"))}function Mo(e,a){const r=document.createEvent("HTMLEvents");r.initEvent(a,!0,!0),e.dispatchEvent(r)}const ha={created(e,{modifiers:{lazy:a,trim:r,number:i}},n){e._assign=er(n);const t=i||n.props&&n.props.type==="number";oa(e,a?"change":"input",l=>{if(l.target.composing)return;let s=e.value;r?s=s.trim():t&&(s=kr(s)),e._assign(s)}),r&&oa(e,"change",()=>{e.value=e.value.trim()}),a||(oa(e,"compositionstart",go),oa(e,"compositionend",Ri),oa(e,"change",Ri))},mounted(e,{value:a}){e.value=a==null?"":a},beforeUpdate(e,{value:a,modifiers:{lazy:r,trim:i,number:n}},t){if(e._assign=er(t),e.composing||document.activeElement===e&&(r||i&&e.value.trim()===a||(n||e.type==="number")&&kr(e.value)===a))return;const l=a==null?"":a;e.value!==l&&(e.value=l)}},ho={deep:!0,created(e,a,r){e._assign=er(r),oa(e,"change",()=>{const i=e._modelValue,n=vo(e),t=e.checked,l=e._assign;if(B(i)){const s=_i(i,n),m=s!==-1;if(t&&!m)l(i.concat(n));else if(!t&&m){const h=[...i];h.splice(s,1),l(h)}}else if(nr(i)){const s=new Set(i);t?s.add(n):s.delete(n),l(s)}else l(jn(e,t))})},mounted:Bi,beforeUpdate(e,a,r){e._assign=er(r),Bi(e,a,r)}};function Bi(e,{value:a,oldValue:r},i){e._modelValue=a,B(a)?e.checked=_i(a,i.props.value)>-1:nr(a)?e.checked=a.has(i.props.value):a!==r&&(e.checked=rr(a,jn(e,!0)))}function vo(e){return"_value"in e?e._value:e.value}function jn(e,a){const r=a?"_trueValue":"_falseValue";return r in e?e[r]:a}const Ho=ge({patchProp:mo},Kt);let qi;function bo(){return qi||(qi=Ct(Ho))}const Ao=(...e)=>{const a=bo().createApp(...e),{mount:r}=a;return a.mount=i=>{const n=xo(i);if(!n)return;const t=a._component;!z(t)&&!t.render&&!t.template&&(t.template=n.innerHTML),n.innerHTML="";const l=r(n,!1,n instanceof SVGElement);return n instanceof Element&&(n.removeAttribute("v-cloak"),n.setAttribute("data-v-app","")),l},a};function xo(e){return se(e)?document.querySelector(e):e}Object.defineProperty(Object.prototype,"forEach",{value:function(e){Object.keys(this).forEach(a=>{e(this[a],a,this)})}});Object.defineProperty(Object.prototype,"reduce",{value:function(e,a){return Object.keys(this).reduce((r,i)=>e(r,this[i],i,this),a)}});Object.defineProperty(Object.prototype,"map",{value:function(e){let a={};return Object.keys(this).forEach(r=>{a[r]=e(this[r],r,this)}),a}});Object.defineProperty(Object.prototype,"filter",{value:function(e=a=>Boolean(a)){let a={};return Object.keys(this).forEach(r=>{e.apply&&e(this[r],r,this)&&(a[r]=this[r])}),a}});Object.defineProperty(Object.prototype,"toArray",{value:function(){let e=[];for(let a in this)e.push([a,this[a]]);return e}});const No=`45
Greetings, stranger. I'm not surprised 
to see your kind here. Many 
adventurers have traveled this way 
since the recent troubles began.
 
No doubt you've heard about the 
tragedy that befell the town of 
Tristram. Some say that Diablo, the 
Lord of Terror, walks the world again.
 
I don't know if I believe that, but a Dark 
Wanderer did travel this route a few 
weeks ago. He was headed east to the 
mountain pass guarded by the Rogue 
Monastery.
 
Maybe it's nothing, but evil seems to 
have trailed in his wake. You see, 
shortly after the Wanderer went 
through, the Monastery's Gates to the 
pass were closed and strange 
creatures began ravaging the 
countryside.
 
Until it's safer outside the camp and the 
gates are re-opened, I'll remain here 
with my caravan. I hope to leave for 
Lut Gholein before the shadow that fell 
over Tristram consumes us all.  If 
you're still alive then, I'll take you 
along.
 
You should talk to Akara, too. She 
seems to be the leader of this camp. 
Maybe she can tell you more.
`,fo=`45
Well met, noble Paladin. It's been a 
while since I've seen any of your kind in 
the west. It would be an honor to aid 
you in any way that I can.
 
No doubt you've heard about the 
tragedy that befell the town of 
Tristram. Some say that Diablo, the 
Lord of Terror, walks the world again.
 
I don't know if I believe that, but a Dark 
Wanderer did travel this route a few 
weeks ago. He was headed east to the 
mountain pass guarded by the Rogue 
Monastery.
 
Maybe it's nothing, but evil seems to 
have trailed in his wake. You see, 
shortly after the Wanderer went 
through, the Monastery's Gates to the 
pass were closed and strange 
creatures began ravaging the 
countryside.
 
Until it's safer outside the camp and the 
gates are re-opened, I'll remain here 
with my caravan. I hope to leave for 
Lut Gholein before the shadow that fell 
over Tristram consumes us all.  If 
you're still alive then, I'll take you 
along.
 
You should talk to Akara, too. She 
seems to be the leader of this camp. 
Maybe she can tell you more.
`,ko=`51
I've been leading my trade caravan 
across the eastern deserts for more 
than twenty years now. I've been 
attacked by bandits and outlaws more 
times than I can remember. But never 
when a Paladin accompanied me. 
 
Indeed, your Order has saved me from 
losing a small fortune over the years. I 
just hope you can discover what's 
going on around here and get the 
Gates to the East opened up!
`,Co=`85
Cain seems to have great wisdom 
regarding the supernatural. I hope I 
never live to be that wise...
`,yo=`58
Akara is the Rogues' High Priestess. She 
sells the few magic items in her 
possession and can even heal your 
wounds. She is very wise and will help 
you if she can.
`,Lo=`66
The fiery Kashya commands the Rogue 
archers in battle. I've only spoken to 
her a few times, though. I get the 
feeling that she doesn't like outsiders 
very much.
`,To=`88
Charsi seems to be a very sweet girl. 
She's the smith around here and can 
help you by trading weapons and 
armor.
`,So=`55
Gheed is a wandering merchant of 
questionable character who is traveling 
along with my caravan to the East. He 
will buy and sell most anything.
 
He's greedy, but his wares are beyond 
reproach. I would suggest keeping both 
eyes open when you deal with him.
`,wo=`71
To the east are lands of great 
mystery... and the Jewel City of the 
Desert, Lut Gholein.
`,Do=`68
I'll gladly take you eastward, if you can 
drive the Evil from the Monastery.  
Then, the Rogues may re-open the pass 
through the mountains.
`,Po=`70
It's easy to become lost in the 
wilderness on the way to the Citadel. 
After you have come to the Cairn 
Stones, you must remember that the 
path continues through the caves.
`,Io=`35
I am Akara, High Priestess of the 
Sisterhood of the Sightless Eye. I 
welcome you, traveler, to our camp, 
but I'm afraid I can offer you but poor 
shelter within these rickety walls.
 
You see, our ancient Sisterhood has 
fallen under a strange curse. The 
mighty Citadel from which we have 
guarded the gates to the East for 
generations, has been corrupted by the 
evil Demoness, Andariel.
 
I still can't believe it... but she turned 
many of our sister Rogues against us 
and drove us from our ancestral home. 
Now the last defenders of the 
Sisterhood are either dead or scattered 
throughout the wilderness.
 
I implore you, stranger. Please help us. 
Find a way to lift this terrible curse and 
we will pledge our loyalty to you for all 
time.
`,Eo=`34
Greetings, young Sorceress. It is good 
to see more of your kind at work in the 
world these dark days. In my opinion, 
the world needs more women to fight 
against the great shadow. But I am 
forgetting my manners... 
 
I am Akara, High Priestess of the 
Sisterhood of the Sightless Eye. I 
welcome you, traveler, to our camp, 
but I'm afraid I can offer you but poor 
shelter within these rickety walls.
 
You see, our ancient Sisterhood has 
fallen under a strange curse. The 
mighty Citadel from which we have 
guarded the gates to the East for 
generations, has been corrupted by the 
evil Demoness, Andariel.
 
I still can't believe it... but she turned 
many of our sister Rogues against us 
and drove us from our ancestral home. 
Now the last defenders of the 
Sisterhood are either dead or scattered 
throughout the wilderness.
 
I implore you, stranger: please help us. 
Find a way to lift this terrible curse and 
we will pledge our loyalty to you for all 
time.
`,Ro=`42
The Sisterhood of the Sightless Eye has 
a long and distinguished history. Over 
the generations our Order has become 
a deadly fighting force as well as a 
bastion for women who sought to forge 
their own destiny.
 
Yet beware, young one, the lure of 
power and knowledge can lead to 
disaster. I have seen ambition foul the 
bravest of hearts and recklessness dull 
hard-won wisdom.
 
You would do well to tread lightly upon 
the dark path you have chosen to 
explore.
`,Bo=`49
I understand that Cain is the last 
descendant of the ancient Horadrim 
and that his knowledge of their lore is 
vast. He could prove to be very useful 
in discerning the nature of our current 
crisis.
`,qo=`49
Kashya has always been fiercely loyal, 
but I fear her anger and frustration 
over these recent events will lead her 
into harm's way. She is highly 
protective of the few Rogues remaining 
under her command and will not send 
them into combat unless there is dire 
need.
`,Go=`46
Charsi is young and innocent. However, 
I believe her Barbarian blood thrills to 
the prospect of adventure and danger. 
She takes great pride in her work and 
finds comfort in the fact that her 
weapons and armor are helping to end 
this evil plague.
`,Uo=`48
Though he has only been our guest for 
a short time, I sense that Warriv has 
faced many harrowing trials. Though 
he knows, as I do, that a terrible evil 
has blanketed the land, his only real 
concern is to reach the eastern trading 
ports with his caravan.
`,Oo=`53
To be honest, I have done my best to 
stay clear of Gheed. He wears 
dishonesty about himself like a cloak 
and seeks only to better his situation 
by preying on the misfortunes of 
others.
`,zo=`55
The wilderness is overrun with Evil and 
the minions of Hell have taken our 
rightful home. We must purge all Evil 
from the Monastery and restore order 
to the world.
`,Fo=`53
I often dream of the day we reclaim our 
own. The Sightless Eye sees through 
the mist of time a great glory ahead, 
but how far ahead the Eye cannot 
discern.
`,Wo=`67
Our mental discipline is matched only by 
our skill in archery... I only hope these 
are enough to withstand this awful 
trial.
`,jo=`59
Beware that you do not suffer the fate 
of the corrupted Rogues. To lose one's 
life is a tragedy, but to lose one's soul 
is even worse.
`,_o=`41
Even though the corrupted ones were 
once of our Order, you need not shy 
from slaying them, for they stand 
between you and Andariel.
 
Perhaps, when the Demon Queen is 
dead, our Sisters will return to life, but 
more likely they will be forever bound 
to their unholy pact.
`,Vo=`56
Welcome, outlander, to our glorious 
hovel. I know you're here to challenge 
the evil that's driven us from our 
ancestral home.
 
But, know this. Akara may be our 
spiritual leader, but I command the 
Rogues in battle. It will take more than 
just killing a few beasts in the 
wilderness to earn my trust.
`,Jo=`55
Well, well, I never expected to see an 
Amazon in these lands. You're very 
brave to have come here. Many of my 
fellow Sisters have fallen under some 
dark spell, and if you're not careful you 
may fall prey to it as well.
`,Qo=`60
When I was very young, Akara told me 
tales of the Amazons' fearlessness in 
battle and of their skills with spears 
and bows. I like to think we Rogues 
have much in common with you 
Amazons.
`,Ko=`64
Some of my Rogues told me of Deckard 
Cain. They said that he is a man of 
great wisdom. Personally, I don't know 
how wise he could possibly be if he 
never learned how to wage battle 
himself.
`,Yo=`57
Akara has been like a mother to me for 
as long as I can remember. She is wise 
and good, but I don't think she has the 
steel to retake our Monastery by force.
`,Xo=`89
I don't trust many outlanders, but 
Warriv seems fine. He never says much 
to me, though.
`,$o=`66
Before our exile, Charsi, our blacksmith, 
could fashion any implement of war.
 
Here in the camp, she merely makes do. 
Her best tools remain within the 
Monastery.
`,Zo=`58
Gheed is a pig. I've been tempted to 
throw him out of the camp many times, 
but Charsi seems to think that he's 
good company. I don't trust the man, 
but if she's comforted by him, then I'll 
desist.
`,es=`76
If we could only find out how Andariel 
has managed to corrupt our Sisters, 
then, perhaps, we could drive out the 
evil clouding their minds.
`,as=`68
In this camp, those of us who have 
remained true to our Order are forced 
to live among common traders and 
farm animals.
 
Welcome to our circle of suffering.
`,rs=`67
Perhaps Tristram deserved its fate... 
for letting Evil loose upon the land. I 
only hope we don't suffer the same.
`,is=`71
Some evenings we gather at the bonfire 
to retell epic tales... and try to forget 
about the terrible events that led to 
losing the Monastery.
`,ns=`47
Hi there. I'm Charsi, the blacksmith here 
in camp. It's good to see some strong 
adventurers around here.
 
Many of our Sisters fought bravely 
against Diablo when he first attacked 
the town of Tristram. They came back 
to us true veterans, bearing some 
really powerful items. Seems like their 
victory was short-lived, though... Most 
of them are now corrupted by Andariel.
`,ls=`54
Wow. You're a Barbarian, huh? It's 
really great to meet you. I've seen a 
few of your kind around here lately. I'm 
a little jealous... I wish I could go off 
adventuring with you.
 
Oh, by the way... I'm Charsi, the 
blacksmith here in camp.
`,ts=`57
You know, I've been with the Sisters for 
as long as I can remember. But Akara 
told me that my real parents were 
Barbarians from the northern tribes 
and that they were killed when I was 
very young.
 
Sometimes I wonder what my life would 
have been like if I had been raised as a 
Barbarian.
 
I don't know. I love being a blacksmith... 
but sometimes I just want to get out 
and explore the world, you know?
`,os=`86
I don't really know anything about Cain. 
He seems to have a lot of secrets... 
That makes me nervous.
`,ss=`51
Oh, Kashya's fantastic. Sure, she's a 
little hard on outsiders, but who can 
blame her? All she wants is to protect 
our Order. But now that our Sisters 
have turned against us... I think this 
whole mess has hardened her heart.
`,cs=`64
Akara, our priestess and seer, is most 
upset by the corruption of our Sisters. 
I fear that she blames herself.
`,ms=`80
Warriv's all right, I guess. He seems too 
serious most of the time. I haven't 
really talked to him all that much.
`,ps=`60
Oh, I like Gheed. He's very funny. He 
has all sorts of interesting stories from 
the places he's been. I wish I could see 
the sights he has.
`,ds=`84
I don't know why some of my Sisters 
chose to follow Andariel. Those who 
strayed were among our finest 
warriors.
`,us=`48
Good day to you partner! I'm Gheed and 
I can already tell that I'll be your best 
friend in this forsaken camp.
 
A spare weapon, some gold, a small 
gem is all I want in exchange for the 
equipment you'll need on whatever 
quests you might undertake.
 
Now, now, now... Don't be shy, all of my 
items are guaranteed for life and come 
with a two-day warranty!
`,gs=`46
A Necromancer! I hoped I'd never have 
to lay my eyes on one of your kind 
again. ... The recent troubles in this 
area have brought out all kinds, I see. 
Nevertheless, your money's good...
 
A spare weapon, some gold, a small 
gem is all I want in exchange for the 
equipment you'll need on whatever 
quests you might undertake!
 
Now, now, now... Don't be shy, all of my 
items are guaranteed for life and come 
with a two-day warranty!
`,Ms=`74
Don't think you can fool me, 
Necromancer. I've seen what your kind 
can do. If you're involved in any of the 
evil out there, I don't even want to 
know. Trade quickly and be about your 
business!
`,hs=`57
That old coot, Cain, is as crazy as a wet 
Quill Rat. I hear he survived whatever 
happened in Tristram. Personally, I 
wouldn't trust a thing he has to say.
`,vs=`55
Akara and Kashya are Sisters in the 
Order of the Sightless Eye, but they are 
worlds apart. Akara is a slow river of 
magic, and Kashya, a viper of war. 
They're both deeply devoted to their 
religious order, yet the corruption of 
their Sisters pains them both to no 
end.
`,Hs=`52
Charsi is a fine girl..., but she has no 
business savvy! I know she means well, 
but the prices she charges for weapons 
and armor will never earn her a profit.
 
As long as I keep filling her mind with 
stories of adventure, she'll never catch 
on to the fact that I'm raking in gold 
hand over fist!
`,bs=`55
Warriv was kind enough to let me travel 
with his caravan, but don't let him drag 
you into a search for a new Eastern 
trade route.
 
I'm making a fortune right here... from 
the Rogues, of course! You, on the 
other hand, always get my best prices!
`,As=`61
Andariel's demonic forces have taken up 
residence in the forests as well as the 
Monastery. Uh-uh. I won't be venturing 
out of the camp. So, if you need 
anything, I'll be right here.
`,xs=`58
When - or if - I get to Lut Gholein, I'm 
going to find the largest bowl of 
Narlant weed and smoke 'til all earthly 
sense has left my body.
`,Ns=`43
Long ago, the Soulstones were given to 
the Horadrim by the Archangel Tyrael. 
They were used to bind the three Prime 
Evils. I now know that even these holy 
artifacts were no match for Diablo's 
power.
 
I hope that his two brothers are more 
securely held... but I fear the worst.
`,fs=`54
It takes time to master your skills... and 
use will hone your technique. But take 
care to choose your new skills wisely.
`,ks=`52
You may recover some mysterious 
things from the demons you kill. Some 
of great use to you... some of great 
peril! Bring them to me and I'll reveal 
their secrets.
`,Cs=`46
Have I told you about the Horadrim? 
They were an ancient confederation of 
mage-clans who sought to bind the 
three Prime Evils for eternity. The 
Horadrim are now nearly forgotten... 
and it appears that the bonds they 
wove are unravelling!
 
As the last of the Horadrim, I pray that 
I can help you remedy their failure.
`,ys=`43
Long ago, Diablo and his brothers were 
cast out of Hell by the Lesser Evils. It 
seems that Hell's balance has shifted, 
as Andariel is now aligned with the 
Lord of Terror. Her presence here in 
the mortal realm does not bode well for 
us.
`,Ls=`90
Turn back! I can tell that you need more 
experience to fight safely in the next 
wilderness.
`,Ts=`46
Halt! You should complete Akara's quest 
before venturing further. Search for 
the Den in the wilderness closer to 
camp.
`,Ss=`116
Beware! The evil is strong ahead.
`,ws=`92
Beware! Beyond lies mortal danger for 
the likes of you!
`,Ds=`88
Take care! The Corrupted Rogues in the 
wilderness ahead are not to be trifled 
with.
`,Ps=`43
There is a place of great evil in the 
wilderness. Kashya's Rogue scouts 
have informed me that a cave nearby is 
filled with shadowy creatures and 
horrors from beyond the grave.
 
I fear that these creatures are massing 
for an attack against our encampment. 
If you are sincere about helping us, 
find the dark labyrinth and destroy the 
foul beasts.
 
May the Great Eye watch over you.
`,Is=`46
I should add that many Rogue scouts 
have died in that horrible place. We 
cannot afford to lose any more. If you 
choose to enter that Den of Evil, you 
must do so alone.
`,Es=`87
The demons in that cave have claimed 
many of my finest archers. I wonder 
how you will fare!
`,Rs=`95
The beasts from the cave have begun to 
roam throughout the countryside. 
You'd better be careful out there.
`,Bs=`95
You seem like a noble warrior. I hope 
you can help us.
`,qs=`67
You're a brave soul! I'd sooner thrust 
my sacred scepter into the foulest, 
carbuncular trull than set one boot 
into that cave.
`,Gs=`122
One who seeks that cave, seeks death.
`,Us=`85
Your task is not complete until you have 
killed all the demons in that cave.
`,Os=`111
You'd better come through on this. Your 
reputation depends on it.
`,zs=`148
You haven't cleared the cave, yet? Do 
you need anything?
`,Fs=`73
Demons still befouling that cave, huh? I 
think you might need a new weapon.
`,Ws=`124
One who hesitates... does so with good 
reason.
`,js=`65
You have cleansed the Den of Evil. 
You've earned my trust and may yet 
restore my faith in humanity.
 
Your reward is training in the skill of 
your choice.
`,_s=`74
Hmm. I'm surprised you survived that 
test, outlander. Go see Akara. She may 
reward you.
`,Vs=`94
You are truly brave and skillful...  Akara 
was worried about you.
`,Js=`87
The only good demon is a dead one, I 
say.
 
By the way, did you happen to find 
anything in that cave you'd like to sell?
`,Qs=`120
...That which does not kill you makes 
you stronger.
`,Ks=`56
My Rogue scouts have just reported an 
abomination in the Monastery 
graveyard!
 
Apparently, Andariel is not content to 
take only our living. Blood Raven, one 
of our finest captains in the battle 
against Diablo at Tristram, was also 
one of the first to be corrupted by 
Andariel.
 
Now, you'll find her in the Monastery 
graveyard raising our dead as 
zombies!
 
We cannot abide this defilement! If you 
are truly our ally, you will help us 
destroy her.
`,Ys=`80
Death has done nothing to weaken 
Blood Raven's combat skills. If 
anything, she's more deadly than ever.
`,Xs=`99
Blood Raven was the leader of a Rogue 
band that once fought Diablo at 
Tristram.
`,$s=`94
I'm sorry... The undead are bad for 
trade. I have a strict no-return policy.
`,Zs=`51
Blood Raven fought valiantly against 
Diablo in the catacombs beneath 
Tristram... She was never quite the 
same afterwards. It is now obvious she 
brought an evil influence back with her.
`,e1=`140
Hmmm...
 
How can one kill what is already dead?
`,a1=`99
Each moment you delay adds another 
undead Sister to Blood Raven's army.
`,r1=`70
If you fail to destroy Blood Raven, I fear 
that our Order will perish forever.
`,i1=`68
Akara felt something was wrong even 
before Andariel descended upon us. 
She feared that Blood Raven had 
stumbled upon some evil force beneath 
Tristram.
 
I wish we had acted then...
`,n1=`77
I wonder if that old gossip, Melra, is 
among the undead? Oh, she had dirt on 
everybody.
`,l1=`86
When the dead return to prey upon the 
living, it is a terror beyond 
understanding.
`,t1=`55
I can hardly believe that you've defeated 
Blood Raven!
 
Though she was once my closest friend, 
I pray that her tortured spirit remains 
banished forever.
 
You have earned my respect, stranger... 
and the allegiance of the Rogues. I 
have placed several of my best 
warriors at your disposal.
`,o1=`122
Andariel must be made to pay for her 
sacrilege!
`,s1=`77
Kashya wishes to reward you for your 
defeat of Blood Raven. I thank you, 
too, even though Blood Raven was once 
my friend.
`,c1=`148
Some of those gals weren't so nice the 
first time around.
`,m1=`104
You've done well, stranger. I hope all 
your efforts are worth it.
`,p1=`50
It is clear that we are facing an Evil 
difficult to comprehend, let alone 
combat.
 
There is only one Horadrim sage, 
schooled in the most arcane history 
and lore, who could advise us... His 
name is Deckard Cain.
 
You must go to Tristram and find him, 
my friend. I pray that he still lives.
`,d1=`90
The bark of Inifuss holds mystical 
runes.
 
Akara can translate them... into our 
revenge!
`,u1=`42
Tristram is too far to journey by foot...  
Cain would likely be dead, when you 
arrived. However, there is a magical 
portal that will take you there 
instantly.
 
To open it, one must stand within the 
circle of Cairn Stones and touch them 
in a certain order. The proper order 
can be found in the runes written on 
the bark of the Tree of Inifuss.
 
You must find the sacred Tree of Inifuss 
and bring back its bark. I will translate 
the runes to unlock the Stones' mystic 
pattern.
`,g1=`117
If you bring back the bark of Inifuss, 
Akara will tell you how to get to 
Tristram.
`,M1=`68
Months ago, I came across a few 
survivors from Tristram. They said 
that Cain had gone half-mad and could 
no longer distinguish fact from 
fantasy.
`,h1=`98
I would sooner micturate in a tankard 
of my own ale than journey to 
Tristram!
`,v1=`150
Without the bark of Inifuss you can't 
find Cain.
`,H1=`76
How will you find Cain without going to 
Tristram? Finding the Tree of Inifuss is 
the first step on your journey.
`,b1=`96
The Tree of Inifuss is hard to find, but 
you'll know it when you see it.
`,A1=`99
Barking up the wrong tree, huh? You'll 
find it, just keep looking.
`,x1=`70
He who seeks that which cannot be 
found must look inside himself for 
further guidance... or look harder!
`,N1=`82
With this scroll you may open a portal 
back to Tristram. Only Akara can 
decipher its logic.
`,f1=`168
Get this to Akara.
 
Only she can understand it.
`,k1=`72
Look, friend... I trade a lot of strange 
items, but I'm not going to start 
dealing in bark. Okay?
`,C1=`86
This looks like gibberish to me. Akara 
may know what to make of it.
`,y1=`64
Ah, very good. I have translated the 
runes on this scroll. You must find the 
Cairn Stones and touch them in the 
order that I have written.
`,L1=`103
Deckard Cain has crucial knowledge 
about the Evils we face. You must find 
him!
`,T1=`92
I have heard that Tristram is now in 
ruins! Without Cain I fear for the ruin 
of all of us.
`,S1=`68
I'm told that Tristram now resembles a 
mead hall... after a Barbarian wedding! 
I will wait here for your most glorious 
return.
`,w1=`82
It is too dangerous to travel to 
Tristram. I won't be leaving here until 
the way is clear!
`,D1=`64
If he still lives, Deckard Cain may be in 
grave peril! You must hurry to Tristram 
before all is lost!
`,P1=`82
You have risked your life to rescue 
Cain. For that we thank you.
 
We must seek his counsel immediately.
`,I1=`78
Again, you amaze me, outlander.
 
The Sisterhood is grateful to you for 
delivering Cain to us. I believe Akara 
has something to tell you.
`,E1=`53
Ah, Cain is here... another customer. I 
haven't been this pleased since a 
love-starved maiden let down a bit 
more than her hair.
`,R1=`102
Akara wishes to reward you for your 
bravery in returning Deckard Cain.
`,B1=`80
Only a brave adventurer could return 
with Deckard Cain. Akara has a reward 
for your valor.
`,q1=`74
As a token of my gratitude, I will 
identify items for you at no charge.
`,G1=`82
...I thank you, friend, for coming to my 
aid.
`,U1=`75
Oh... Blessings on the Rogues! They 
finally rescued me from that cursed 
place!
`,O1=`33
Regrettably, I could do nothing to 
prevent the disaster which devastated 
Tristram. It would appear that our 
greatest fears have come to pass. 
Diablo, the Lord of Terror, has once 
again been set loose upon the world!
 
As you know, some time ago Diablo was 
slain beneath Tristram.  And when our 
hero emerged triumphant from the 
labyrinth beneath town, we held a 
grand celebration that lasted several 
days.
 
Yet, as the weeks passed, our hero 
became increasingly aloof. He kept his 
distance from the rest of the townsfolk 
and seemed to lapse into a dark, 
brooding depression. I thought that 
perhaps his ordeal had been so 
disturbing that he simply could not put 
it out of his mind.
 
The hero seemed more tormented every 
passing day. I remember he awoke 
many times -- screaming in the night -- 
always something about 'the East'.
 
One day, he simply left. And shortly 
thereafter Tristram was attacked by 
legions of foul demons. Many were 
slain, and the demons left me to die in 
that cursed cage.
 
I believe now that Tristram's hero was 
that Dark Wanderer who passed this 
way before the Monastery fell.
 
I fear even worse, my friend... I fear 
that Diablo has taken possession of the 
hero who sought to slay him. If true, 
Diablo will become more powerful than 
ever before.
 
You must stop him or all will be lost.
`,z1=`36
...And so it came to pass that the 
Countess, who once bathed in the 
rejuvenating blood of a hundred 
virgins, was buried alive... And her 
castle in which so many cruel deeds 
took place fell rapidly into ruin. Rising 
over the buried dungeons in that 
god-forsaken wilderness, a solitary 
tower, like some monument to Evil, is 
all that remains.
 
The Countess' fortune was believed to 
be divided among the clergy, although 
some say that more remains unfound, 
still buried alongside the rotting skulls 
that bear mute witness to the 
inhumanity of the human creature.
`,F1=`110
The only wealth you're likely to find 
there is a wealth of vermin.
`,W1=`70
That old tower is as rotten on the inside 
as it appears on the outside. I heard 
that several Sisters came to a 
gruesome end when a stairwell 
collapsed on them.
`,j1=`67
The dangers there are not solely 
architectural. Once inside that 
wretched place, many succumb to a 
vile miasma.
`,_1=`60
That tower marks a place of danger. 
There is an epic poem about it...  How 
much sorrow one can stand was tested 
there.
`,V1=`81
Rumors of treasure are no different 
from rumors of any other kind. They 
hold false promise to those who should 
know better.
`,J1=`78
The tome speaks of treasure. Yet, all we 
have found are death, delirium, and 
disappointment.
`,Q1=`151
Have you suddenly lost your taste for 
wealth?
`,K1=`94
Quickly in and quickly out is all the 
advice I can give you.
`,Y1=`118
Better an empty pocket than a full 
grave.
`,X1=`170
You're not ready to give up, are you?
`,$1=`140
There is no more I can tell you about 
that ancient tower.
`,Z1=`79
Guess what! I've named a boil on my 
ass after you. It, too, bothers me every 
time I sit down.
`,e0=`79
Your rewards are well-earned. To us, 
the tower was nothing more than a 
headstone looming over a long 
forgotten grave.
`,a0=`62
Remember. Wealth is as insubstantial 
as a cloud and passes as quickly. 
Ignore Gheed. All that twitters is not 
bold.
`,r0=`68
Warriv's advice is like corpse gas; it 
befouls the air for a moment and then 
it disappears.
`,i0=`58
I thought the stories of treasure in the 
tower were nothing but lies. I am glad 
you found something of value in that 
death-trap. Would that our Sisters had 
been so fortunate.
`,n0=`126
Those riches will serve you well on the 
long road ahead.
`,l0=`69
Well done, my friend. Courage and 
opportunity together have created in 
you a kind of alchemy.
`,t0=`66
When I fled the Monastery, I left behind 
the Horadric Malus, my enchanted 
smithing hammer. If you can retrieve it 
for me, I'll use its magic to strengthen 
your equipment.
`,o0=`51
The Malus was forged and enchanted by 
the ancient Horadric Mages during the 
Sin Wars. When their union dissolved, 
the Malus was entrusted to the 
Sisterhood guarding the pass into the 
East.
`,s0=`59
The retrieval of the Horadric Malus is 
not without risk. Our Monastery is 
filled with voracious hellspawn. You'd 
best be careful, my friend.
`,c0=`61
Charsi is wasting her time and talents 
using an inferior hammer! Had she the 
Horadric Malus, she could make the 
steel sing and craft you a suit of armor 
as impenetrable as the Great Eye.
`,m0=`87
The Monastery can confuse even those 
who know it well. Stay alert in there.
`,p0=`74
Charsi talks of nothing anymore, but 
this Horadric Malus. Between you and 
her my ears need a rest.
 
Just find it and bring it back quickly.
`,d0=`74
I have offered my nomadic phallus, but 
to no avail.
`,u0=`68
Just as an archer needs bow and arrow, 
or a draughtsman pen and paper, so 
Charsi needs the Horadric Malus with 
which to ply her trade.
`,g0=`57
The Malus has eluded you so far. Well, 
search thoroughly in the Barracks... 
That is where the Rogues kept their 
forge.
`,M0=`98
If you can't carry out this quest, how 
will you face the greater evils ahead?
`,h0=`71
To do battle with Andariel requires 
more than thick skin and a strong will. 
You'll want armor and weaponry forged 
with the hammer's enchantments.
`,v0=`89
The Malus is a Horadric artifact of 
great power. Please bring it back.
`,H0=`90
I have heard that you bear us no Malus.
`,b0=`120
What better opportunity to show your 
mettle?
`,A0=`59
The magical effects imbued by the 
Malus are impossible to predict, but 
are always to the good.
`,x0=`57
Well done, my friend. But remember, the 
return of the Horadric Malus is but one 
step in reclaiming the Monastery.
`,N0=`74
Now that the Horadric Malus is back in 
our possession, we shall use it to 
deliver a great blow against the Evil 
which torments this land.
`,f0=`72
Oh! Thanks so much for returning the 
Horadric Malus! I will now imbue one of 
your items with magical powers.
`,k0=`120
I guess it's too late to take back some 
of the names I called you.
`,C0=`118
I am glad the hammer has returned and 
you with it.
`,y0=`34
It is certain that we face the demon 
queen, Andariel, who has corrupted the 
Rogue Sisterhood and defiled their 
ancestral Monastery. This does not 
bode well for us, my friend.
 
Ancient Horadric texts record that 
Andariel and the other Lesser Evils 
once overthrew the three Prime Evils -- 
Diablo, Mephisto and Baal -- banishing 
them from Hell to our world. Here, they 
caused mankind untold anguish and 
suffering before they were finally 
bound within the Soulstones.
 
Andariel's presence here could mean 
that the forces of Hell are once again 
aligned behind Diablo and his Brothers. 
If this is true, then I fear for us all.
 
You must kill her before the Monastery 
becomes a permanent outpost of Hell 
and the way east lost forever.
`,L0=`45
Diablo is heading east for some foul 
purpose. And the only passage east is 
through the Monastery gate. 
Obviously, Diablo summoned Andariel 
to block any pursuit.
 
For her part Andariel hopes to win 
Diablo's favor... the lesser demons are 
always vying for positions of power 
within the unholy hierarchy!
`,T0=`63
Andariel has desecrated all we hold 
dear. She must not be permitted to 
serve Diablo.
 
Destroy her! Her corruption of our 
Order must be undone!
`,S0=`132
Send Andariel back to the Hell she came 
from!
`,w0=`71
You're going after Andariel?
 
... One of my wagon wheels is in need of 
repair. I'll be under the wagon, if I'm 
needed.
`,D0=`72
The mapmakers tell us the shortest 
distance between two points is a 
straight line.
 
Our way east is a line that runs through 
Andariel's stronghold, the Monastery.
`,P0=`81
I can imagine a thousand different ways 
to kill Andariel. You need only choose 
one.
`,I0=`48
It is clear that Andariel is acting on 
behalf of Diablo to prevent anyone 
from following him eastward. Her 
defeat would allow you to continue the 
pursuit.
 
Ancient lore has it that while Andariel 
was spawned in the Burning Hells, she 
is not fond of fire.
`,E0=`57
You have done much to help us, but I 
sense that this has only fueled 
Andariel's fury. She will not stop until 
we are all dead.
 
You must kill Andariel before her army 
can gain the upper hand.
`,R0=`72
Have you stumbled upon that Demon 
Queen, yet? I hear she's quite the 
beauty... as far as Maidens of Anguish 
go, that is.
`,B0=`108
If you are the hero that you seem to be, 
now is the time to prove it.
`,q0=`90
May I remind you that my caravan can 
only go east, if the Monastery is 
cleansed?
`,G0=`126
Deckard Cain has important information 
about Andariel.
`,U0=`64
Finally, we may rejoice!
 
We owe you a debt we can never repay. 
I only hope that in time we will be able 
to rebuild our Order.
 
All our thanks go with you, my friend.
`,O0=`86
You'll probably go east now... It was 
good to know you. I hope you'll come 
back if you ever need anything.
`,z0=`44
Andariel's death brings about renewed 
life for us all. We mourn the loss of our 
dear Sisters, but at least now we can 
get on with our lives.
 
I... may have misjudged you, outlander. 
You are a true hero and testament to 
the noble spirit which has inspired our 
Order for generations.
 
Fare well... my friend.
`,F0=`100
I'm going to party like it's 999!
`,W0=`82
The caravan is prepared. We may now 
journey eastward to Lut Gholein.
`,j0=`38
This is a great victory indeed, but many 
more battles await. I will accompany 
you on your journey, lending what 
assistance I can... 
 
Remember... Diablo is still out there, 
seeking something in the desert. I'm 
afraid that this nightmare will not end 
until you find what it is that he seeks.
`,_0=`600
Halt.
`,V0=`290
You may not pass.
`,J0=`255
Welcome to the palace.
`,Q0=`255
You may enter the palace.
`,K0=`290
Stay out of trouble.
`,Y0=`58
I'll bet you wonder how this town 
manages to stay safe with all the 
trouble going on out in the desert. 
Well, I can tell you that it's got nothing 
to do with the local town guards... 
they're all in the palace for some 
reason.
 
Jerhyn hired me and my mercenaries to 
help keep the peace around here. We're 
not cheap, but we're the best this 
wasteland has to offer.
`,X0=`85
We do a good job in town, but beyond 
the city gates, you'll find all manner of 
demons.
`,$0=`52
The local guards were all relocated to 
the palace after the troubles began. No 
one really knows why. Actually, all of 
the town's brothel girls have been 
hiding out in the palace's cellar lately, 
so I assume that the guards have been 
assigned to 'protect them' with their 
lives.
`,Z0=`75
I might spare you a few of my men. 
Why, enough gold can muster an army.
`,e5=`61
Jerhyn's got a nice little trading post 
going here. Despite his youth, he is a 
clever businessman. As you can see by 
that palace, he's done quite well for 
himself.
`,a5=`99
We're keeping the town safe and tight, 
but I've got a hunch there's something 
Jerhyn's not telling us.
`,r5=`44
Ah, Elzix is quite a character. I had a 
few run-ins with his band of outlaws in 
my younger years. Now, he's as settled 
as the dunes out there. The Desert Rain 
Inn is his pride and joy these days.
`,i5=`53
Atma seems to be a fine woman. But I'm 
sure the loss of her family has made 
her lonely. Perhaps I should go over 
and console her when I get off duty 
tonight...
`,n5=`72
Geglash is an imposing warrior, but he's 
never been able to back down from a 
fight. One of these days, his pride will 
be the death of him.
`,l5=`67
Meshif has sailed all around the 
southern seas and visited many 
strange lands. It must be driving him 
mad, having to stay anchored here.
`,t5=`70
I haven't talked much to Fara. She 
keeps to herself most of the time. I get 
the feeling that she doesn't like us 
mercenary types much.
`,o5=`73
I'd stay clear of Lysander, if I were you. 
He's always mixing his damned potions 
and chemicals. I wouldn't be surprised 
if he winds up blowing himself to 
smithereens!
`,s5=`85
Drognan's a mystery to me. Then again, 
I never did trust mages much.
`,c5=`61
Hmm... You look like a sturdy 
adventurer.
 
You know, I used to be quite the 
scoundrel in my day. I led the fiercest 
group of bandits who ever terrorized 
these sands!
 
Nowadays, I run this here Inn and 
pretty much stay out of trouble.
 
My days of adventuring are behind me.
`,m5=`48
Ah... You must be one of the new 
heroes who've come to rid our city of 
evil. Under any other circumstances, I'd 
be surprised to see one of your kind in 
the city. But lately... Oh, never mind all 
that...
 
You know, I used to be quite the 
scoundrel in my day. I led the fiercest 
group of bandits who ever terrorized 
these sands!
 
Nowadays, I run this here Inn and 
pretty much stay out of trouble.
 
My days of adventuring are behind me.
`,p5=`52
You know, I've lost a number of body 
parts over the years. An eye here, a leg 
there...
 
Say, do you know any spells that'd grow 
them back for me? Hmm... On second 
thought, I'll leave well enough alone.
`,d5=`90
What tales Drognan can tell... You 
would do well to listen carefully to that 
wizened wizard.
`,u5=`80
There are many ancient tombs in the 
desert. Most of them are already 
plundered, but I imagine that some 
have remained hidden.
`,g5=`67
I miss the brothels that used to do 
business here.
 
You know, all of the ladies fled to the 
palace as soon as the trouble in the 
desert started. You'd think that they 
could at least come out once in a while 
now that Greiz and his men have things 
relatively under control.
`,M5=`71
Atma... Now, there's a fine woman. 
Lately, though, she's only thinking 
about revenge. She has reason 
enough...
`,h5=`71
We've all fared well under Jerhyn's 
leadership. The town has remained 
safe throughout this whole mess; and 
yet the lad still seems very upset about 
something.
`,v5=`88
Geglash is a fool who would fight his 
own shadow if he could. Fighting's all 
he ever thinks about!
`,H5=`74
Meshif is a wise Captain, I think. Wise 
enough to know silver from tin and 
truth from dung, that's for sure.
`,b5=`65
Fara is a good woman. She seems very 
sad, but seldom speaks of her past. 
She's good to the poor and helps 
people when she can. That makes her 
all right in my book.
`,A5=`70
That Lysander's a grumpy old cuss. 
You'd better not disturb him while he's 
working on his potions, or... BOOM! 
You could get blasted to the moon.
`,x5=`62
Now that Andariel is dead, I can return 
and outfit the Rogues properly. Once 
I've made some trades here, I'll be free 
to head back to their Monastery. Let 
me know if you want to travel along.
`,N5=`106
Caravans take people where they want 
to go - until they get there.
`,f5=`80
By ship is the only way eastward from 
here. I believe Captain Meshif has a 
small trading vessel moored at the 
docks.
`,k5=`70
There used to be a lot of brothels 
here... I guess the troubles scared all 
the women away, or maybe they're 
'safe' in Jerhyn's palace.
`,C5=`53
That old desert fox, Elzix, is as crafty 
as they come. Years back, he made off 
with a small fortune of my caravan's 
wares. I certainly never expected to see 
him so... domesticated.
`,y5=`57
Jerhyn has his father's strength and 
wits. He's young, but he rules this 
place with wisdom and care. I think 
he'll grow into a fine Sultan... Provided 
we all survive this crisis.
`,L5=`59
You'll forgive me if I seem upset. I've 
suffered a loss recently, but that's not 
your problem.
 
It's a relief to see some proper warriors 
come through here. My name is Atma. I 
run the tavern here in Lut Gholein.
`,T5=`86
Evil has laid siege to Lut Gholein and 
you may be our last hope...
`,S5=`56
This public house used to be quite lively, 
until this plague of evil. Luckily, I've 
managed to save away a tidy nest egg. 
Unfortunately, I couldn't save 
everything I cared for...
`,w5=`57
In addition to my public house, there 
used to be several brothels doing 
business here. When the troubles first 
started in the desert, the harem guilds 
sought sanctuary within the palace.
 
Of course, Jerhyn was glad to oblige. I'll 
bet they're finding many ways to repay 
him for his protection.
`,D5=`70
Geglash may seem like a sot, but he's a 
brave man. All this trouble has driven 
him to drinking more than his usual.
`,P5=`64
Elzix and I have reached an 
understanding over the years. He 
sends travelers to me for drink and 
entertainment, and I send them back to 
him for a soft bed. The travelers often 
trade their wares for lodging.
`,I5=`89
Meshif seldom patronizes my 
establishment. I think he prefers to 
stay out there on his leaky ship.
`,E5=`71
Oh, Lysander is cranky, but he's a good 
old man. He used to give me medicines 
when... my son was ill.
`,R5=`78
Drognan is a very private person. He's 
always studying ancient scrolls and 
such. He may be a mystery to me 
forever.
`,B5=`57
Bah! I don't know why you people keep 
pestering me.
 
Greiz seems to have this place locked 
down nice and tight. Not that I couldn't 
have done the same! I've proven my 
valor in combat plenty of times.
`,q5=`43
Hey, you're a Barbarian, aren't ya? 
Ferocious as the wild beasts of the 
north, that's what they say. I suppose 
you've come to help save this city. You 
needn't bother.
 
Greiz seems to have this place locked 
down nice and tight. Not that I couldn't 
have done the same! I've proven my 
valor in combat plenty of times.
`,G5=`46
Hey, I heard that you Barbarians can 
wield multiple weapons at once. I never 
learned to fight two-handed. Carrying a 
sword and a wineskin at the same time 
is all I can ever handle.
`,U5=`53
Sure, I hear lots of what goes on. Did 
you hear about the harem guilds? They 
were the only ones allowed to hide out 
in the palace when the raids started!
 
Ah... It figures.
`,O5=`64
I've killed plenty of those demons out in 
the desert. It doesn't seem to slow 
them down any, though... they just 
keep coming back for more.
`,z5=`55
Have you found those big sand maggots 
yet? Arrows and all that don't work so 
well against them. Best thing is to hack 
'em with a sword or such.
`,F5=`58
There are some ancient tombs out there 
in the desert. You have to go pretty far 
to find them, though. Rumor has it that 
they're crawling with walking corpses 
now.
 
As if the Saber Cats and Claw Vipers 
weren't bad enough.
`,W5=`67
Yeah. Meshif's okay, I guess. But I'll be 
damned if I ever get on his ship. I don't 
even like to drink water.
`,j5=`52
Jerhyn's been acting strange lately. I 
can't imagine why he recalled the town 
guards into the palace. If there is 
something wrong in there, I hope he 
doesn't expect me to handle it.
`,_5=`57
I've seen Fara defend herself against a 
few drunken ruffians. She's got moves 
I've never even seen before. Wherever 
she's from, she sure learned how to 
fight there.
`,V5=`83
I've got no time for old alchemists. 
Lysander would be completely useless 
in a real fight.
`,J5=`63
Greetings. I'm Meshif, captain of this 
ship here. I make port runs around the 
Twin Seas and occasionally out to 
Kingsport in Westmarch.
 
I haven't sailed anywhere lately, 
though... Jerhyn has ordered me to 
stay docked here in case of emergency.
`,Q5=`54
Greetings, Amazon. I haven't seen one 
of your kind in many years.... It's good 
to know that warriors of your caliber 
are protecting this city.
 
I'm Meshif, captain of this ship here. I 
make port runs around the Twin Seas 
and occasionally out to Kingsport in 
Westmarch.
 
I haven't sailed anywhere lately, 
though... Jerhyn has ordered me to 
stay docked here in case of emergency.
`,K5=`62
I was wondering if you've heard any 
news from Kurast? I know you 
Amazons travel extensively. Have you 
been there recently?
 
Hmm... Well, I hope the port opens 
soon. I need to get home to Kurast and 
find out what's been happening there.
`,Y5=`72
There's something Jerhyn's not telling 
me, I just don't know what. To my eye, 
things here in town don't look that bad, 
especially since Warriv's caravan route 
opened up.
`,X5=`65
I've been all around the seas in these 
parts. It's dangerous sailing west this 
time of year, though. Until the season 
changes, the caravan through the 
desert is the main trade route to 
Westmarch.
`,$5=`75
My ship is the only way East from here. 
Still, Lord Jerhyn tells me that I may 
not leave until the current crisis is 
over.
`,Z5=`65
Oh, I've known Elzix for years. He 
always offers me a free room at his Inn 
when I dock here, but I prefer the 
comforts of my own cabin.
`,ec=`61
Warriv is a good friend. We've shared 
many tales, he and I. If we had it all to 
do over again, I believe we'd both be 
explorers of some renown.
`,ac=`69
Greiz seems to be a dependable fellow. I 
hope he can handle it if those things in 
the desert decide to attack this town.
`,rc=`130
Atma serves a fine ale in her 
establishment.
`,ic=`70
Hah! That braggart Geglash says he 
fears neither man nor beast. Yet, when 
I offer to take him out to sea, he 
quakes with fear.
`,nc=`130
The lady Fara has a proud, noble air 
about her.
`,lc=`41
Greetings, honored traveler. I am 
Jerhyn, Lord of Lut Gholein, and I bid 
you welcome to my fair port-city. I'm 
glad to know that once again caravans 
are free to travel through the Western 
Pass.
 
For some time now, we have been under 
siege by an evil power that I cannot 
identify. Strange... It all began when a 
Dark Wanderer came this way, looking 
for the Tomb of Tal Rasha. No one 
knows exactly where Tal Rasha, Keeper 
of Baal, is entombed, but it is certain 
to be far out in the desert.
 
Now, my people whisper tales of the 
dead rising from their tombs and 
horrible creatures lurking amongst the 
moonlit dunes. Even I have witnessed 
things which I cannot explain. I've 
ordered the port closed and all trade 
ships moored until I am sure that my 
city is safe.
 
Atma, the tavernkeeper, has an 
important mission for you. Go see her 
immediately. You'll find her on the 
other side of town.
 
Now, I must return to the palace. I 
apologize, but I can't invite you in. 
Things are... rather a mess right now.
`,tc=`51
For trade in magic and the like, see 
Drognan or Lysander. Drognan is the 
wisest man I know - without equal in 
magic and ancient lore. Poor Lysander 
is nearly deaf, but he's a reliable potion 
chemist.
 
For travel back west, see Warriv, whom 
you already know.
 
Our own Fara is a fine and honest 
armorer, and she can heal wounds as 
well.
 
Elzix is the Innkeeper and may also 
have some items to trade.
 
Greiz, the mercenary captain I hired to 
secure the gates of Lut Gholein, keeps 
order in town, as well.
 
There are others here, too. I'm sure 
you'll meet most of them. Just look 
around...
`,oc=`117
Things are getting worse by the hour. I 
know everything looks fine, but trust 
me, it isn't!
`,sc=`117
Things are getting worse by the hour. I 
know everything looks fine, but trust 
me, it isn't!
`,cc=`63
To any who aid me in the defense of Lut 
Gholein, I pledge my support. Passage 
East, wealth, honor - all are due to 
those who help my city.
`,mc=`71
You seem very capable, but no offense 
is intended when I say that I must 
choose my confidants carefully. It 
wouldn't do to have rumors sending 
everyone into a panic.
`,pc=`87
Even though he was once a bandit, I 
permitted Elzix to take over the Desert 
Rain Inn. He has been quite civilized 
ever since.
`,dc=`76
When you arrived, Warriv's caravan had 
been long overdue. With all of the evil 
that's arisen in the land, I'm surprised 
he got through at all.
`,uc=`77
Meshif is an honorable man, but I fear 
that he is growing impatient with me 
about impounding his ship. I dare not 
tell him what's really happening in this 
city.
`,gc=`98
The woman, Atma, may have some 
useful gossip for you. She can always 
be found near her public house.
`,Mc=`81
I know much about the ancient 
religions. I was trained as a Paladin of 
Zakarum in the Eastern Kurast temple 
many years ago.
`,hc=`103
Welcome, brother Paladin.
 
I am Fara. I was once a devout 
champion of Zakarum.
`,vc=`67
Perhaps, in time, you will play a part in 
reclaiming our Order's honor and 
spirit. You are an inspiration to me, 
brother Paladin.
`,Hc=`60
The shrines in the desert are leftover 
artifacts from the great Sin War that 
ravaged these lands almost a thousand 
years ago. They still function, but most 
travelers believe them only to be 
remnants of the distant past.
`,bc=`54
I've no love for brothels, as they can 
lead honorable men to do dishonorable 
things. Since the local harems took up 
hiding in the palace, however, there 
seems to be a rise in foul tempers.
`,Ac=`66
When the Three Evils were bound ages 
ago, Mephisto, the Lord of Hatred, was 
moved to Kurast and bound by the 
holiest of magics.
`,xc=`79
Warriv may not remember me, but I 
helped him out when I was a young 
Paladin. There's no need for me to 
remind him. The rewards for honor will 
not come in this life.
`,Nc=`68
Greiz is a fine warrior and leader, but in 
his heart, he will always be a 
mercenary for hire. I cannot be loyal to 
those who have no loyalty to 
themselves.
`,fc=`90
Atma is a good, loving woman. But I 
fear she will succumb to her despair 
and hatred.
`,kc=`95
Geglash is too confident in his abilities. 
A warrior's true strength is in his 
heart.
`,Cc=`94
Meshif is an honest man as far as I can 
tell. He has never pestered me about 
my past.
`,yc=`61
How do I know I can trust you? Hmm?
 
You may be as shifty as that pack rat, 
Elzix, who runs the Inn. But, if you 
need a potion, though, I suppose I can 
make you one... for a price, of course.
`,Lc=`109
Potions are delicate mixtures. They're 
just as liable to go off in your face as 
anything.
`,Tc=`65
Ah... The sweetest desert flower - that's 
Atma. Even my strongest brew can't 
bring back her family, though.
`,Sc=`86
There are some ancient enchanted 
fountains in the desert that can heal 
your wounds - if you drink enough from 
them.
`,wc=`71
Oh. Deafness has its advantages, you 
know. I'm no longer forced to overhear 
the tedious gossip of others.
`,Dc=`54
I never patronized the brothels, mind 
you. But since those ladies took up 
hiding in the palace, there certainly has 
been less scenery to feast my eyes on.
`,Pc=`95
Oh... I have great faith in Greiz. He 
seems to have things well in hand.
`,Ic=`90
I've traded my potions to Warriv many 
times. Yes. They seem to fetch a good 
price in the western lands.
`,Ec=`71
I've sold many sea-sickness potions to 
Meshif over the years. It seems that 
many of his passengers don't take well 
to the rocking of his ship on the open 
seas.
`,Rc=`58
Oh... Young Jerhyn used to purchase 
minor love potions from me, hoping to 
win the favors of the harem girls.
 
But now that the girls have taken up 
residence in the palace, he doesn't 
come around here anymore. Well, 
well... I've always said, 'alchemy is no 
substitute for experience'.
`,Bc=`57
Drognan? Oh.. He's a good friend of 
mine. I help him find exotic spell 
components and alchemical books from 
time to time. I think he used to be a 
sorcerer of great renown, but he 
doesn't like to talk about his past.
`,qc=`61
I've heard that you are responsible for 
banishing Andariel back to the Burning 
Hells. I'm impressed, stranger. That 
couldn't have been easy.
 
My name is Drognan and I know what 
you're up against, my friend.
 
You ought to look over my inventory of 
items for trade.
`,Gc=`50
Welcome, young Sorceress, to Lut 
Gholein. I hope your skills are a match 
for the horrors that lie beyond the 
city's walls. A mage of your limited 
experience may find the evil too great 
to withstand alone.
 
My name is Drognan and I know what 
you're up against, my friend.
 
You ought to look over my inventory of 
items for trade.
`,Uc=`74
Many of the Mage Clans feel that 
women shouldn't practice magic 
openly. But since you've made it this 
far, I must say that you have proven 
your right to do so.
`,Oc=`57
The Horadrim were a powerful Order, 
although maybe too prideful. Tal Rasha 
was one of their Order. And that 
should tell you something.
 
Any man who believes himself strong 
enough to contain one of the Prime 
Evils is in for a rude awakening, I 
should think.
`,zc=`78
I have heard of your friend, Cain. He is 
the last of the Horadrim. You would do 
well to heed whatever advice he has to 
give you.
`,Fc=`53
Not long ago, one of my Vizjerei 
comrades, who I believed had died in 
Tristram, came to this city. He seemed 
quite insane, so I dismissed much of 
what he said.
 
However, he was able to talk his way 
into Jerhyn's palace. No one has seen 
him since. I fear that fool may have 
found something in the palace that led 
to his doom.
`,Wc=`68
I've been practicing magic for more 
years than you could know. I'm older 
than I look, though not so old that I 
can't conjure up a few sparks.
`,jc=`67
Elzix is a sly one, I'll give him that. Of 
course, he never tries to cheat me. He 
knows what my magic skills can do.
`,_c=`86
Demons have spread throughout the 
desert wasteland and threaten to 
engulf our quiet port-city.
`,Vc=`88
Meshif and his vessel should remain 
here, lest we risk taking demonic 
stowaways to other lands.
`,Jc=`58
When the recent troubles began, Lord 
Jerhyn came seeking my council. I 
advised him to close the port and put 
the town under strict watch.
 
Lately, though, he's been occupied 
within the palace. I doubt his whores 
could divert him from his civic duties 
for this long, though.
`,Qc=`68
Lysander is harmless enough. We keep 
each other company with our mutual 
interests, yet I don't think he could 
handle the enormity of our present 
situation.
`,Kc=`48
Greetings, my friend. Have you spoken 
to Jerhyn yet? He's quite a remarkable 
leader for being such a young man. 
Then again, the old blood has always 
run strong in this land.
`,Yc=`71
There is something about Fara that 
troubles me. Her manner is strange for 
a lonely desert-maid.
`,Xc=`70
Elzix is quite a scoundrel, but I like him 
all the same.
`,$c=`59
I talked at length with Warriv as we 
crossed the desert from Khanduras. He 
has many fascinating tales of the 
dangers in the desert. His experience 
may be useful to you.
`,Zc=`57
Meshif is an interesting man. Part of 
him longs for the freedom of the open 
seas... Yet his heart belongs in his 
homeland.
`,e2=`42
I thank you, mortal, for my freedom. 
But I did expect you earlier.
 
I am the Archangel Tyrael. I came here 
to prevent Diablo from freeing his 
brother, Baal. But I have failed. Now, 
Terror and Destruction roam free 
throughout your world.
 
Even now, they head towards the 
Eastern capital of Kurast - to the very 
heart of the Zakarum Temple. There 
they hope to find their eldest brother, 
Mephisto, the Lord of Hatred who was 
imprisoned there ages ago.
 
If the three Prime Evils unite, they will 
be invincible. Though it is unclear as to 
what their aims are, it is certain that 
they must be stopped at all costs.
 
I am broken and the energies that tie 
me to this world are diminishing 
rapidly.
 
You must take up this quest and 
prevent the Three Brothers from 
reuniting. You must cross the sea and 
search for Diablo and Baal in Kurast.
 
Now hurry, mortal... Time is running 
out for all of us!
`,a2=`50
Hey, hero! You're asking for trouble, if 
you leave town now.
`,r2=`50
I don't expect this of you, but if you 
want to help me, I would be grateful.
 
In the sewers below our city, there lurks 
a horrid creature that hungers for 
human flesh. The creature has killed 
many, including my son and my 
husband.
 
If you destroy it, I will reward you. 
Please be careful though, that beast 
has taken enough from us already.
 
The sewer entrance is through the trap 
door just up the street.
`,i2=`52
I've personally found some of that 
devil's victims washed up out of the 
sewer. Often, they are missing limbs or 
a head, and their bodies have always 
been skinned.
 
At first the creature raided the town at 
night... That's how Atma lost her 
family. Now we've got him barricaded 
in the sewers.
 
You're safe up here on the surface, but 
every now and again some fool wants 
to be a hero and heads down to the 
waste tunnels with a pig-sticker.
`,n2=`68
I hear that the creature kills his victims 
in order to hack off their limbs! I guess 
that makes me a less likely candidate, 
eh?
`,l2=`84
I've heard tales of walking corpses out 
in the desert at night, though I've never 
actually seen one.
`,t2=`77
Hey... Don't touch my drink or I'll bore a 
hole into your skull with my thumb.
`,o2=`54
I believe that the creature you refer to 
is one of the ancient Horadric 
mummies from the tombs that lie 
buried beneath the desert sands. It is 
unusual for one of his kind to be so far 
away from his resting place. I sense in 
this entity a restless and malevolent 
spirit.
`,s2=`62
The creature makes its lair in the 
tunnels beneath this city. He butchered 
my husband and son... I simply cannot 
bear to talk about it...
`,c2=`63
There are two entrances to the sewers, 
I believe. One of them is right near 
here, down by the water beneath the 
docks. I can see it from my ship, and 
you can bet I keep an eye on it every 
night.
`,m2=`53
Fara and I have been talking about the 
creature recently. From my studies, I 
have deduced that it is Radament the 
Fallen, an ancient Horadric mummy 
that has for some reason left his tomb 
to prey on mortals.
 
I'm doing some more research now. If 
you check back later, I may have some 
more insight as to his nature.
`,p2=`94
I hear that beast is after body parts. 
Does he eat them? Oooh... Ghastly!
`,d2=`48
The Horadrim used to mummify their 
highest mages, and infuse them with 
spells that would allow them to protect 
their tombs, even after death.
 
I have no idea why one of them would 
be acting so malevolently. Perhaps 
Drognan or Fara would know more 
about this.
`,u2=`90
Death is not afraid of the living, but the 
living abhor death.
`,g2=`55
I noticed a rotting, human arm floating 
in the harbor this morning. I suspected 
foul play, so I told Greiz. He didn't 
seem too concerned since there haven't 
been any folk reported missing lately.
`,M2=`83
I am starting to have second thoughts 
about my request... I couldn't bear the 
thought of you losing your life on my 
behalf.
 
Please be careful.
`,h2=`69
We've been meaning to send an 
organized group down there to kill that 
thing, but it would be dangerous. We 
just can't afford the chance of losing 
any men with all the trouble that's 
going on in the desert.
`,v2=`65
Ah-hah! Back for a small shot of 
courage... Believe me, it doesn't help 
for long.
 
Drinks, barkeep!
`,H2=`69
If you're going to fight that thing, use 
some common sense. Be knowledgeable 
about what harms the undead. Poison, 
for instance, will have little effect.
`,b2=`64
Huh? Peppermint? Oh, Radament! Yes, 
yes. Ooh, a foul creature...
 
Some of my exploding potions should do 
quite nicely against him. They usually 
work well against the undead.
`,A2=`49
I've just been reading something 
interesting about this sort of undead. 
Apparently, certain Horadric funereal 
priests altered the bodies of their dead 
mages with magical and surgical 
techniques -- often replacing body 
parts with those of animals.
 
This was thought to augment their 
powers, and raise their status in the 
afterlife.
`,x2=`68
Drognan told me something interesting 
earlier today. It might explain why 
Radament is so restless, and it might 
have something to do with why he is 
stealing human body parts.
`,N2=`41
The Horadric mummies were created to 
protect the tombs, but Radament is far 
from his burial chamber. Given the 
aberrations that have been witnessed 
lately, it comes as no surprise that 
even the ancient guardian spells have 
begun to unravel. Be wary of this as 
you venture farther into the desert.
`,f2=`76
You've killed Radament, eh? That's quite 
a nice piece of work! If you ever need a 
job as a mercenary, I'd be happy to 
sign ya' up.
`,k2=`52
From what you tell me, it would seem 
that Radament was bent on the task of 
reviving his own mummified corpse 
with the flesh of the living.
 
This is very unusual indeed. It takes an 
incredible magic power to alter the 
singular purpose of an undead mind.
 
Perhaps there is a power at work here 
which is beyond my ken.
`,C2=`61
Uh... Little of what I am able to hear is 
of any value. Radament's death, 
however, is news worth hearing. I'm 
sure Atma will be glad to hear of this.
`,y2=`62
Good job mate! At night out on my ship, 
I was often awakened by that fiend's 
awful moaning. I bet I rest easier now.
`,L2=`41
Whoah oh... 'Radament the Fallen', is it?
 
I've fallen off many a barstool and no 
one calls me 'Geglash the Fallen'. They 
might go so far as to say, 'Geglash, 
you've fallen!'
`,T2=`70
We ran into one of those old tomb 
guardians when I ran with my bandits. 
I know they aren't easy foes to face, so 
you sure have my respect. Have you 
told Atma yet?
`,S2=`142
Atma's been telling everyone what 
you've done for her.
`,w2=`102
As you have helped Atma and all of us, 
so shall I help you.
`,D2=`57
If you haven't already, tell Atma that 
Radament is dead. It may help to ease 
the weight of her mourning.
`,P2=`50
They say that the taste of vengeance is 
bittersweet, but I find it to my liking. 
 
In addition to my undying gratitude, I 
have spoken on your behalf with the 
rest of the townspeople. The 
merchants have agreed to show their 
gratitude by offering their wares and 
services at lower rates.
 
Oh... Jerhyn wants to see you, too. 
You'll find him in front of the palace.
`,I2=`37
Ahh... The lost Horadric Scroll! What a 
fortunate turn of events...
 
As the last living Horadrim, I alone have 
knowledge of its meaning. Now, to read 
the Horadric runes it bears. Hmmm...
 
The Horadric Mages, after binding Baal 
within Tal Rasha, magically sealed off 
his Burial Chamber from the mortal 
realm. Those same Mages also crafted 
fearsome Horadric Staves and imbued 
them with the special power to open 
the Chamber's hidden door.
 
After nearly losing one to the thievery 
of a rogue sorcerer, they divided all 
the Horadric Staves into two parts - 
wooden shaft and metal headpiece - 
hiding them separately to safeguard 
them.
 
The Horadrim foresaw our current 
plight and designed the hiding places 
to reveal themselves to worthy heroes 
like you.
 
Collect both parts of a Horadric Staff 
and unite them using a Horadric Cube. 
Then, you may enter Tal Rasha's Burial 
Chamber.
`,E2=`50
The Viper Amulet you bear is actually 
the headpiece of a Horadric Staff!
 
Yes... You have an uncanny knack for 
finding rare and valuable artifacts. Of 
course, you'll have to use a Horadric 
Cube to combine the headpiece with the 
shaft.
`,R2=`56
The Staff of Kings! You astound me, my 
friend. You have discovered the shaft 
portion of a Horadric Staff.
 
I trust you know how to use a Horadric 
Cube to unite the shaft with its 
headpiece.
`,B2=`40
You have quite a treasure there in that 
Horadric Cube. According to Horadric 
lore, the Cube can restore a Horadric 
Staff.
 
To do it - use the Cube as you would a 
scroll. When the Cube opens, place 
both pieces of the Staff into it and use 
the Cube's transmute power.
 
You'll be pleased to know that the Cube 
has other alchemical uses as well...
 
Six gems plus one sword transmute into 
a socketed long sword.
 
You may also transmute two quivers of 
crossbow bolts into one quiver of 
arrows, while two quivers of arrows 
yield one quiver of bolts.
 
I must leave it to you to discover other 
formulae.
`,q2=`46
Excellent! You have a Horadric Staff.
 
Carry it with you into Tal Rasha's Tomb. 
Find within the Tomb the chamber 
whose floor is inset with the Circle of 
Seven Symbols.
 
Place the Staff into the receptacle you 
find there. That will open the secret 
passage into Tal Rasha's Burial 
Chamber.
 
But, be prepared for a fight - you'll 
likely have to kill Tal Rasha to destroy 
Baal.
`,G2=`110
My astrologers failed to predict this 
eclipse. You should seek Drognan's 
advice.
`,U2=`71
This midday darkness reeks of foul 
magic! My men and I are trying to keep 
the peace, but this kind of thing really 
scares people.
`,O2=`65
Two men arrived late last night bearing 
a story about evil magic. They said 
they saw a gathering of giant snake 
creatures performing some arcane 
ritual. They sound like the Serpent Men 
of the desert.
`,z2=`72
The sun has grown disgusted with the 
terrible deeds it must shine upon each 
day. Damnation is upon us all.
`,F2=`121
Drognan, the wizard, will have some 
idea as to what is happening.
`,W2=`100
This whole place is one big ale fog.
`,j2=`70
This unnatural nightfall is no doubt 
caused by evil sorcery. Drognan might 
know what we are dealing with.
`,_2=`65
Claw Vipers! This outer darkness 
mirrors the inner blackness of their 
souls. It is they who have eclipsed the 
sun, I'll wager. They are a venomous 
band.
`,V2=`77
I've been researching this lengthy 
eclipse and I believe it to be the work 
of Claw Vipers.
 
Find their temple beneath the desert 
sands and you may find the source of 
this curse.
`,J2=`76
This permanent darkness is very 
unsettling. Hmmm... It would make 
navigation by stars easier for me, 
though.
`,Q2=`62
Drognan may have some advice on this 
matter. Hmm... I think I'll speak with 
him myself.
`,K2=`130
This eclipse is a definite manifestation 
of evil.
`,Y2=`73
Don't worry! My men and I have an iron 
grip on this town. If those cursed Claw 
Vipers are plotting anything against 
us, we'll be prepared for 'em.
`,X2=`73
The calculated coldness of the reptilian 
brain makes the Claw Vipers uncanny 
adversaries.
`,$2=`49
It's strange when the morning after the 
night before... is still the same night.
`,Z2=`105
I've had about enough of this darkness. 
I don't even know what day it is 
anymore.
`,em=`77
The Claw Vipers practice evil magic. 
They have also been known to kidnap 
travelers and sacrifice them to their 
dark gods.
`,am=`82
Well... I don't know much about the 
habits of Claw Vipers, to be honest. 
Drognan will probably know something 
about the nature of the magic at work.
`,rm=`51
I've discovered a reference to a similar 
eclipse several hundred years ago. It 
says that some desert-dwelling snake 
demons had erected an evil altar, 
which caused the sun to go black.
 
Perhaps we are dealing with something 
similar here. Look for an altar in the 
Claw Viper temple.
`,im=`94
I usually charge for rooms by the night.
 
But I may have to soon change that.
`,nm=`57
The source of this spell is probably a 
magical altar. It will not be enough to 
kill the Claw Vipers. To reverse the 
spell you must destroy the altar.
`,lm=`80
I was going to go to bed, but then I 
realized that I have no idea what time 
it is. It could be the crack of dawn, for 
all I know.
`,tm=`96
The sun again shines on Lut Gholein! I'm 
beginning to like you, traveler.
`,om=`219
I'm glad that's over with!
`,sm=`74
Ahh... It takes but one eye to revel in 
the beauty of our restored sun.
`,cm=`60
So, this is daylight... It's over-rated.
`,mm=`80
With renewed daylight, one may gather 
the wits that were scattered about like 
restrictive undergarments in the 
darkness.
`,pm=`130
So... Did you plunder any booty?
`,dm=`132
You have done well to restore light to 
our world.
`,um=`87
Drognan seems to have taken you into 
his confidence. This is good, for you 
will benefit from his wisdom.
`,gm=`69
Ahhh... Claw Vipers are fond of magical 
artifacts. Did you happen to find one in 
their temple?
`,Mm=`69
You did well in destroying the Claw 
Vipers. We are all glad to see the sun 
returned to its former glory.
`,hm=`48
I've been speaking with Lord Jerhyn, and 
I sense that he is becoming more and 
more agitated by something. You 
should try to talk to him again.
 
If he still won't take you into his 
confidence, seek to prove yourself a bit 
more. I gather that his respect for you 
is growing.
`,vm=`41
I've been researching the old records, 
trying to find the location of Tal 
Rasha's Tomb. Though I haven't found 
the Tomb, itself, I may have a good 
lead for you.
 
The great Vizjerei Summoner, Horazon, 
built his Arcane Sanctuary somewhere 
around here. He was a powerful 
spellcaster and kept demons as slaves 
within the Sanctuary. He kept a close 
eye on great events, too -- such as the 
imprisonment of Baal within Tal 
Rasha's Tomb.
 
If you could find Horazon's Sanctuary, 
I'm sure that it would hold some clue 
as to the Tomb's location. Though I 
doubt Horazon is still alive, you must 
proceed with caution. There's no telling 
what could be waiting inside.
 
When I spoke of this with Lord Jerhyn, 
he asked that I send you to him. 
Perhaps he knows of a secret entrance 
or the like.
`,Hm=`46
Ah, the ancient mage Horazon! He 
believed that he could bend Evil forces 
to his will. What he didn't know was 
that Evil uses man, not the reverse.
 
The Vizjerei still revere him as a symbol 
of man's ability to triumph over other 
worldly forces. The Church of Light, 
however, cites him as an example of 
man's folly.
`,bm=`89
The only thing in Jerhyn's cellar are the 
harem girls that have been hiding there 
since the troubles began.
`,Am=`62
An 'Arcane Sanctuary' under the 
palace? I'd heard that there were some 
underground cellar levels that Jerhyn 
used as chambers for his treasure and 
such, but no Arcane Sanctuary.
`,xm=`44
When the troubles began here, I allowed 
the terrified Harem guilds to join me 
within the safety of the palace. All was 
fine, until one night...
 
Screams echoed up the stairwells from 
the harem. My guards arrived to find 
the poor girls being slaughtered by a 
merciless band of hell-spawned 
demons. My brave guardsmen tried to 
push the demons back into the 
mysterious rift from which they came.
 
Ever since, my men have fought a losing 
battle. Demons have continued to pour 
through the rift into the palace. 
Ultimately, I hired Greiz and his 
mercenaries to help protect the rest of 
my fair city.
 
Drognan believes that the Arcane 
Sanctuary lies buried underneath this 
palace, since Lut Gholein occupies the 
site of an ancient Vizjerei fortress.
 
My palace is open to you now... Take 
care.
`,Nm=`45
I very much doubt that Horazon still 
lives in his Sanctuary. He possessed 
great power and influence over 
demons, but even that may not have 
been enough in the end. One of his 
notoriety cannot easily remove himself 
from the vengeful reach of Hell.
`,fm=`60
Look, look... I'm just about as tough and 
arrogant as they come, but you'd never 
catch me trying to tame a demon for a 
pet. That's just asking for a lot of 
trouble.
`,km=`75
Arcane Sanctuary? That place sounds 
awful! Even if you find a way into it, 
what makes you think you'll be able to 
leave again?
`,Cm=`73
A careful caravan gives wide berth to 
sleeping bandits. If Horazon is gone, 
let him remain so.
`,ym=`49
Horazon found it necessary to lock 
himself up for all time, just to protect 
himself from those angry demons. 
Such is the fate of one who practices 
the summoning arts... that, or eternal 
damnation. There's old summoners and 
bold summoners, but no old, bold 
summoners.
`,Lm=`42
Nearly a thousand years ago, Horazon 
rose to the fore of the Vizjerei mage 
clan. Horazon used the knowledge of 
the Vizjerei to summon and control 
demons from Hell.
 
Though a powerful Summoner, Horazon 
feared that the Lords of Hell would 
punish him for enslaving their 
brethren. Thus, the Summoner created 
for himself an Arcane Sanctuary.
 
He believed that his Sanctuary would 
not only protect him from Hell's 
vengeance, but also allow him to 
continue his studies free from the 
ravages of time and disease.
 
Horazon had crafted many wondrous 
scrying devices through which he 
observed the events of the world 
outside. It is certain that he took 
careful study of Tal Rasha's 
imprisonment and recorded the 
location of his forgotten Tomb.
 
The Arcane Sanctuary was believed to 
have been constructed here in Lut 
Gholein. An entrance may be hidden 
somewhere in the palace, as that 
building is very old, and was once a 
Vizjerei fortress.
`,Tm=`57
Ahh... The legend of Horazon is an old 
one, especially around these parts. You 
wouldn't believe the feats and strange 
events that are attributed to him.
`,Sm=`63
I understand that you've been talking to 
Jerhyn. Well, if so, then you're the first 
in a long while... since the trouble 
began, actually.
 
Do us a favor and try to find out what's 
got Jerhyn so edgy all the time. OK?
`,wm=`48
There was an eastern mage... a Vizjerei, 
I believe... who visited me almost a 
year ago. He was very interested in the 
history of this site, and he seemed 
particularly fascinated with the palace 
architecture.
 
I gave him a tour. When he found the 
ancient seals over a passageway in the 
cellar, he became very agitated. He 
asked for some time alone to study 
them, and I granted it.
 
Shortly after, he left with no further 
word and I never saw him again. Odd... 
Don't you think?
`,Dm=`61
What's got you so occupied in the 
palace? Don't tell me you're finding the 
Harems more compelling than killing 
demons? That would be out of 
character for one such as yourself.
`,Pm=`63
I am certain that you will find the 
information you need when you find 
Horazon's Journal. I suggest you find it 
quickly, for Diablo may be getting 
closer to freeing his brother as we 
speak.
`,Im=`68
Huh? The horizon is always out of 
reach, you should know that. Oh, 
Horazon! Oh, I see. Uh.
 
Yes. Well. He was insane. Brilliant, yes, 
but... total lunatic.
`,Em=`57
Even a sanctuary such as Horazon's 
can be breached by the tentacles of 
Evil. Such a haven could have become a 
chamber of unspeakable horrors. Be 
wary of what you may unleash!
`,Rm=`49
All my years of brawling, of pummeling 
both the unsuspecting and the 
deserving, have yielded two insights. 
You can either fight or you can run. All 
other strategies are variations of 
these.
`,Bm=`77
So... Now that you're such a pal of 
Jerhyn, why don't you ask him if I can 
set sail one of these days? I'm running 
out of patience.
`,qm=`87
So you've been in the palace, have you? 
Tell me, why does Jerhyn keep that 
place locked up so tight?
`,Gm=`87
Fate is like a caged gorilla. It will pelt 
you with dung if you mock it.
`,Um=`51
I've been thinking about the problems in 
Jerhyn's palace. Perhaps this has 
occurred to you as well...
 
If those cellar passageways lead to the 
Arcane Sanctuary, then that is where 
the demons came from. Horazon's 
haven must have been breached!
`,Om=`37
Seekers of the Tomb of Tal Rasha will 
find it through the Portal. But know 
that the glowing glyphs recorded here 
in my Arcane Sanctuary are the signs 
of the six False Tombs.
 
The missing Seventh Sign marks the 
Tomb of Tal Rasha... Of the Horadrim 
he might be called the foremost.
 
It was a shining - but brief - moment for 
the Mage Clans when they set aside 
their differences and worked together 
against the common enemy.
 
The Horadrim relentlessly pursued the 
Three across the desolate Empires of 
the East, and even into the uncharted 
lands of the West, leaving the 
Archangel Tyrael's hands unblemished.
 
Presuming the Three to be vanquished, 
the Horadrim's unstable fellowship 
began to dissipate. Abandoning their 
sacred charge to safeguard the three 
Soulstones, the disparate Mage Clans 
began to squabble amongst each other 
over petty differences.
 
Their conflicts not only dissolved their 
brotherhood, but strengthened the 
Evils which they had buried beneath the 
cold earth.
`,zm=`59
Unbelievable! The Harem girls are dead! 
The palace guards have been fighting 
off demons from the cellar. How could 
that happen without my knowledge?
`,Fm=`62
I thank you for your heroic aid! I'm also 
glad that you found something you 
were looking for. The journal should 
help you find the True Tomb of Tal 
Rasha. Hopefully, there is still time to 
get there before Diablo.
 
Go now. And good luck.
`,Wm=`55
You have found Horazon's Journal. 
Excellent... But, I must caution you.
 
The mark of the True Tomb of Tal 
Rasha, is sought, if not already known, 
by Diablo. I needn't elaborate on the 
implications of that.
`,jm=`71
News of the tragedy in the palace is 
spreading fast. How awful! And to 
think, this whole time I thought Jerhyn 
and his guards were in there playing 
with the harem girls.
`,_m=`60
Hah! I wish Jerhyn would've let me in the 
palace. I would've saved those girls and 
kicked demon ass back to the fire-pits 
o' Hell!
`,Vm=`52
So... Now we know Jerhyn's little secret. 
Well... I guess I can see why he wanted 
me to stay, though... I'm just glad it 
didn't come to that. Now he tells me to 
wait some more, in case you need to 
get out of here.
 
Well, for you I'll do it. Maybe they'll 
mention me in the epic ballads, eh?
`,Jm=`67
Well, the news going around town is 
very unsettling. Apparently, we were in 
more danger than anyone thought.
 
Good work friend... you may have saved 
all our skins.
`,Qm=`64
Faith is stronger than any armor. The 
shield will protect the body, but Faith 
will strengthen the courageous heart.
`,Km=`55
Horazon's urinal? Oh, journal! Yes, 
well... Glad you found it. Such a shame 
about those poor harem girls, huh? I 
shall miss them deeply... I mean their 
conversations, of course.
`,Ym=`62
Oh, those poor women! Will the 
slaughter never end? Thank you once 
again for protecting our city.
`,Xm=`57
You must move quickly now, friend, for 
Diablo is undoubtedly close to finding 
what he seeks. Find the Tomb of Tal 
Rasha before he frees the Lord of 
Destruction.
`,$m=`89
That guy really talks like that? Sounds 
like either Horazon has gone stir-crazy 
or that's some impostor.
`,Zm=`57
The man you describe is probably not 
Horazon.
 
He sounds like the very mage who came 
around here a while ago. He was very 
curious about this palace and seemed 
especially interested in the seal on the 
passageway in the cellar. He left 
shortly after that. I wonder how he got 
down there? The seal was never 
broken...
 
That mage spoke a great deal to 
Drognan. Why don't you ask him about 
it?
`,ep=`47
Yes... The man you speak of sounds like 
the mage who came here many months 
ago. He claimed to have fought Diablo 
in the passages beneath Tristram.
 
No doubt the fool wandered into 
Horazon's Sanctuary and lost whatever 
was left of his ravaged mind. He is 
beyond salvation. 
 
It is possible that the fool has been 
possessed by the spirit of Horazon. If 
that's true, then you'd better put an 
end to his tortured existence.
 
Once done, I believe the demons who 
were summoned and imprisoned within 
the Sanctuary will cease to exist as 
well.
`,ap=`57
Ah, yes. I remember. There was a... 
fellow around here many months ago 
who asked almost as many questions 
about Horazon as you.
 
So... He discovered enough to assume 
Horazon's place in the Arcane 
Sanctuary, huh? What a fool!
`,rp=`72
Ah, yes. As a ship captain I am well 
aware of the phenomenon of a false 
Horazon.
 
Sorry, just a little joke.
`,ip=`99
There's nothing more dreadful than a 
powerful being driven by a frayed 
mind.
`,np=`105
You always seem to find the worst 
trouble. I don't know how you handle it.
`,lp=`38
So! Horazon's crazy, eh? I'd be 
surprised if he wasn't. All those 
centuries without ale would drive 
anyone to drink... but then you couldn't 
drink. And that would drive you to 
drink... Hah?... What was the question?
`,tp=`63
Hmmm... That doesn't sound like 
Horazon. I'll agree that he may have 
gone mad, but from what you tell me, I 
don't think that's the case. Talk to 
Drognan... he may know more than I.
`,op=`106
Ugh... Crazy mages give me the creeps.
 
Just kill him and get on with your 
business.
`,sp=`45
The appearance of the mage you 
describe sounds like one I met back in 
Tristram. Many Vizjerei came to fight 
against Diablo, the Lord of Terror. 
Perhaps, this is one of them.
 
You know, fate seems to have frowned 
upon all of the heroes who confronted 
that terrible Evil. Take care or the 
same may happen to you.
`,cp=`76
So, Horazon's been dead for some time. 
I take it you at least found what you 
were looking for.
`,mp=`60
The way I see it... Well, it's all pretty 
blurry.
`,pp=`63
The demonic force that was emanating 
from the corrupted Sanctuary has 
dissipated. I thank you greatly for your 
help. Now, we can look to rebuilding 
our lives.
 
All will be for nothing, though, if you do 
not stop the greater Evil which is 
rapidly gaining ground.
`,dp=`83
Larger forces are moving inexorably 
towards us. You must now make haste 
to the Tombs.
`,up=`65
You make me long for the days of glory. 
When I had both hands, both eyes and 
more of a foot...
`,gp=`84
I guess you'll be heading to the Tombs 
now? I hear that they're in the deepest 
desert regions.
`,Mp=`100
Well! You've got what you're after. Now 
get a move on before it's too late.
`,hp=`103
Huhhh... Such is always the fate of 
those who meddle with evil.
`,vp=`89
You're more the hero than I could have 
dreamed. Perhaps, there is hope for us 
after all.
`,Hp=`74
I feel no pity for that would-be 
Summoner. His terrible ambition for 
demonic power was his undoing. You 
merely hastened the inevitable.
`,bp=`48
I hope that this false Summoner found 
peace in death. Unfortunately, it is 
more likely that he will be dragged 
down into Hell by the demons he was 
bound to.
 
Let this be a lesson to you... Demonic 
magic is a quick path, but its powers 
are seductive and deadly.
`,Ap=`45
I have heard of your many deeds of skill 
and bravery. I feel I can trust you with 
something I have been hesitant to 
speak of...
 
Drognan and I have concluded that the 
Dark Wanderer who passed through 
here recently was Diablo, himself! 
Drognan believes that Diablo is 
searching the desert for the secret 
tomb where the great Horadric mage, 
Tal Rasha, keeps Baal imprisoned.
 
You must find Diablo and put an end to 
the terrible evil that has fallen upon 
our city. Drognan is wise and is sure to 
have some helpful advice for you as to 
how Tal Rasha's tomb may be found.
 
It may take you quite some time to find 
The Tomb. May you be ready when you 
do.
`,xp=`53
It is well-known that there are seven 
great Horadric tombs hidden beneath 
the sands in the furthest reaches of 
the desert. One of them surely must be 
Tal Rasha's prison. You must explore 
each of the tombs to find Tal Rasha's 
exact location.
 
Of course, Diablo is searching for the 
Tomb as well... No one can guess as to 
what terrors he has unleashed in his 
search.
`,Np=`59
So... You're going to search for the 
Seven Tombs, huh? Don't you know 
that they're just desert legends passed 
between merchants and travelers? No 
one really believes that they exist.
`,fp=`61
Be very careful, my friend. I think I've 
seen enough recently not to doubt that 
these Tombs exist. And if they do, 
they're most certainly guarded by 
terrible creatures.
`,kp=`67
I've heard legends of the Tomb of Tal 
Rasha, but I thought they were just old 
tales meant to scare young children.
`,Cp=`59
Ohh... I'd go with ya' to those tombs... 
But... umm... I don't like all that living 
dead stuff.
`,yp=`84
I'm sorry, I can't help you much here. 
Now, if the tombs were across the 
ocean, then I'd be the guy to talk to.
`,Lp=`57
Legend has it that Tal Rasha lies 
imprisoned within his tomb, forever 
struggling to keep the Lord of 
Destruction bound. His was a selfless 
act, although perhaps foolhardy.
`,Tp=`56
When Tal Rasha chose to embody the 
spirit of Baal, he knew his doom was to 
wrestle eternally against the will of the 
greater Evil. Look around you and ask 
yourself, 'Has the battle been won or 
lost?'
`,Sp=`55
Tal Rasha's tomb is hidden deep in the 
desert among six others. Tal Rasha's 
symbol marks the True Tomb. If you 
want to know what that symbol is, you 
should be able to find it within the 
legendary Arcane Sanctuary.
`,wp=`57
Diablo nears his goal. We have little 
time to lose.
 
Remember, my friend, that Andariel 
gave herself willingly to Diablo's cause. 
It would be prudent to assume that the 
other Evils will attempt to aid their 
master as well.
`,Dp=`106
If you're going into the deep desert, why 
not hire a few of my men to watch your 
back?
`,Pp=`47
You have done very well. Few could have 
come this far, let alone discover the 
True Tomb of Tal Rasha. Unfortunately, 
I hear that Diablo and Baal have eluded 
your grasp. This is most unfortunate...
 
If you wish to travel East, I have 
authorized Meshif to give you passage 
by sea. I imagine he should be very 
anxious to leave by now.
 
Good luck on your quest, and thank you 
again for saving my beloved city. You 
will always be welcome in Lut Gholein, 
my friend.
`,Ip=`71
I heard that Diablo has managed to 
best you, at least for the time being. I 
hope you catch up with him soon, and 
send him back to Hell for good!
`,Ep=`70
I'm sorry things didn't turn out as you 
had hoped. Go and remember us 
fondly. You know, you bothered me far 
less than most.
`,Rp=`64
You have proven to be the greatest of 
heroes, and I am honored to call you 
friend. Thank you for bringing peace to 
our lives again.
`,Bp=`68
Never fear, my friend. You did the best 
you could.
 
I suspect that Diablo and Baal are now 
heading east, towards Kurast. You'll 
find them... I know you will.
`,qp=`46
This is terrible news! Baal is in 
possession of one of mankind's most 
powerful mages, and the Lord of Terror 
guides his path. They must be stopped, 
for I am sure they mean to free their 
elder brother Mephisto, the Lord of 
Hatred, who lies imprisoned under the 
corrupted city of Kurast.
 
I fear you are walking into a great evil, 
but your faith can save you. May you 
walk in the light always.
`,Gp=`54
You're an inspiration! And such a hero 
that it makes me look twice as bad...
 
Ahh, you're OK... Hey! Just save some 
glory for us little guys, huh?
`,Up=`51
This is a serious setback... It is most 
unfortunate that Tal Rasha has been 
consumed by Baal's destructive 
influence. There are many secrets 
known to the Horadrim, which could be 
used by Baal against us.
 
You must travel east by sea to Kurast 
and stop Diablo and Baal before they 
free their eldest brother, Mephisto.
 
Hahh... The lands of the eastern Empire 
are not the same as they used to be. 
There has been little word for some 
time.
 
Speed is of the essence. Go quickly, my 
friend. May the fates smile on you.
`,Op=`82
Jerhyn tells me I should take you east to 
Kurast. I haven't been there for several 
years, but rumor has it that things are 
pretty grim.
`,zp=`51
I've heard that your foe got away from 
you this time. Well, look at it this way... 
you've got the demons on the run. If 
you're going to be leaving, then... Well, 
thanks for your help.
`,Fp=`39
The Archangel Tyrael was the one who 
gave the Soulstones to the Horadrim 
two hundred and sixty years ago.
 
It is highly unusual for the forces of 
Heaven to so directly interfere with 
man's destiny, but Tyrael was said to 
act of his own volition. We have never 
been able to discern why.
 
Perhaps, he goes against the consensus 
of Heaven because he doubts our 
ability to defend ourselves, or perhaps, 
he sees more threat than his peers.
 
Where the actions of Hell often seem 
straightforwardly bent on destruction, 
the motives of Heaven are 
unfathomable.
 
Now make haste... Both Diablo and Baal 
must be stopped before they join with 
their brother, Mephisto. If the three 
Prime Evils unite once again, the world 
as we know it will be no more.
`,Wp=`48
Greetings, hero. I've heard of your 
exploits and... I'm quite impressed. 
Very few mortals are capable of 
dealing with the Three and their 
minions as you have.
 
My name is Natalya. I am a hunter of 
Evil, part of an ancient Order sworn to 
hunt down corrupted sorcerers.
 
If I could, I would gladly join your quest 
to stop the Three. But I must wait here 
for further news. I can't predict what 
will happen, but the danger is greater 
than we can know.
 
Until I receive my orders, I'll assist you 
with the information I have.
`,jp=`74
Asheara...? Oh, she's is a tough-talking 
mage, but I'd wager she's never faced 
true Evil.
 
Pampering drunken mercenaries is one 
thing, but standing face to face with a 
hell-spawned demon is another.
`,_p=`69
I've heard the name of Deckard Cain 
many times. He's the last of the 
Horadrim, and thus, I must honor him. 
You must be powerful, indeed, if one 
such as he accompanies you.
`,Vp=`100
Hratli is a master craftsman. My Order 
could make use of one with his unique 
skills.
`,Jp=`67
My Order has been keeping watch over 
Ormus for many years, now. He seems 
to champion the cause of good, but 
who knows what shadow lurks within 
his soul?
`,Qp=`45
I've not set foot in glorious Kurast for 
many years. But I never would have 
imagined it could be so corrupted.
 
Certainly, this must be Mephisto's work! 
You'd best get going, my friend. Diablo 
and Baal are still out there and you 
must find them.
`,Kp=`62
Seeing his homeland in such a state 
must be horrifying to Meshif. I'm 
surprised he's willing to remain here in 
order to help you.
`,Yp=`82
Asheara seems like a very tough 
woman. I'd be careful around her if I 
were you.
`,Xp=`53
Drognan told me of Hratli when we were 
in Lut Gholein. He said that he weaves 
magic into his forge and produces 
mystical weapons and armor.
 
His skills could be quite useful to you. 
`,$p=`44
Judging from his dress and strange 
markings, I would guess that Ormus is 
from the ancient Taan mage-clan. Yet 
none of the others here seem to know 
that he is a sorcerer.
 
The Taan were once as powerful as the 
Vizjerei clan, but their studies were 
even more secretive. I wonder what 
he's hiding.
`,Zp=`49
Have you met, Natalya? She appears to 
be a member of the Khral-Harzhek, a 
secret order that has been around for 
centuries... almost as long as the 
Horadrim, itself.
 
Her presence here makes me uneasy, 
for they are traditionally sworn to hunt 
down Magi who have betrayed the trust 
of their order.
 
I wonder why she is here.
`,ed=`73
Ormus would like you to think him mad. 
Better to watch his actions than listen 
to his words.
`,ad=`33
Welcome to Kurast, traveler. Few come 
willingly to this ancient city anymore. I 
hope you brought your wits with you, 
for sanity is in short supply here.
 
My name is Hratli. I am a sorcerer 
skilled in metal work. It'd be a pleasure 
to help you... I don't have many 
customers these days.
 
As you can see, the populace has been 
brutally decimated by the forces of 
Mephisto. The canals run red with 
blood and demons roam the land.
 
The wretched jungle-hell has already 
reclaimed much of Kurast. The only 
safety you'll find is here at the 
dockside, where a magical warding 
holds the jungle evils at bay... but I 
don't know how long it will last.
 
To make matters worse, the Children of 
Zakarum are in league with the forces 
of Mephisto. The Zakarum have 
concentrated their power in the Temple 
City of Travincal, located within Kurast 
deep in the jungle wilderness.
 
It's true... Their zeal is unmatched. But I 
say the so-called 'Warriors of Light' are 
nothing more than the twisted puppets 
of a hidden hand.
`,rd=`33
Welcome to Kurast, young Sorceress. 
Few come willingly to this ancient city 
anymore. I hope you brought your wits 
with you, for sanity is in short supply 
here.
 
My name is Hratli. I am a sorcerer 
skilled in metal work. It'd be a pleasure 
to help you... I don't have many 
customers these days.
 
Though my own magic is only useful for 
making enchanted weapons, I'll bet 
yours will put an end to this terrible 
evil once and for all. May the spirits of 
Skatsim watch over and protect you.
 
As you can see, the populace has been 
brutally decimated by the forces of 
Mephisto. The canals run red with 
blood and demons roam the land.
 
The wretched jungle-hell has already 
reclaimed much of Kurast. The only 
safety you'll find is here at the 
dockside, where a magical warding 
holds the jungle evils at bay... but I 
don't know how long it will last.
 
To make matters worse, the Children of 
Zakarum are in league with the forces 
of Mephisto. The Zakarum have 
concentrated their power in the Temple 
City of Travincal, located within Kurast 
deep in the jungle wilderness.
 
It's true... Their zeal is unmatched. But I 
say the so-called 'Warriors of Light' are 
nothing more than the twisted puppets 
of a hidden hand.
`,id=`48
You're very brave to have come here. In 
the old days, mages who didn't belong 
to one of the great Mage Clans were 
hunted down as renegades. But now, 
the Mage Clans have little authority.
`,nd=`53
Within the Temple City stands a tower 
built long ago by the Horadrim to 
imprison the... Well, you'll discover 
more about it soon enough.
`,ld=`60
If you are another follower of Zakarum, 
I've told you people before I don't want 
your Towering Spire or anything else 
you have to sell!
`,td=`74
Some find my prices unreasonable. That 
is because I am unreasonable.
`,od=`76
You'll find that the Zakarumites have 
the persistence of zombies, but without 
the charisma.
`,sd=`60
Asheara leads the mercenary company 
known as the Iron Wolves. You can hire 
some of them, but many are occupied 
securing the dockside.
`,cd=`74
Alkor is a potion dealer given over to a 
life steeped in ceaseless study and 
dissipation.
`,md=`58
Ormus is a man of many mysteries. I 
sense strong magic about him, but he's 
never spoken of it to me.
`,pd=`49
I trust you already know Meshif. But did 
you know that he was born and raised 
here?
 
I suspect that like many of us his spirit 
is near broken at the sight of Kurast's 
decline. Only our brand of gallows 
humor saves us from utter despair.
`,dd=`55
This, Cain, whom you brought with you. 
He has the bearing of great power, yet 
I sense no magic about him. He is an 
enigma to me.
`,ud=`49
Natalya is a quiet one. She arrived here 
about a week ago and has pretty much 
kept to herself. She's inquired about 
my weapons a few times, so I assume 
that she's a warrior of some sort.
`,gd=`51
Well, I gave you my word, and brought 
you here as promised.
 
But by all that's still holy, I wish I'd 
never returned to this accursed place. 
This fetid jungle can't be the fair 
Kurast I left behind.
 
I don't know what all this evil is, my 
friend, but it's obvious that you must 
stop it. I only pray that you can before 
the jungle consumes the last vestiges 
of my beloved homeland.
`,Md=`47
Being a Barbarian, I'm sure you've seen 
many strange sights in the northlands.
 
But by all that's still holy, I wish I'd 
never returned to this accursed place. 
This fetid jungle can't be the fair 
Kurast I left behind!
 
I don't know what all this evil is, my 
friend, but it's obvious that you must 
stop it. I only pray that you can before 
the jungle consumes the last vestiges 
of my beloved homeland.
 
If this evil isn't contained, it could 
spread north to your homeland, too. 
Then the whole world would fall under 
the shadow of the Three.
`,hd=`63
It takes great courage and generosity 
to defend a land and a people that are 
not your own. Perhaps, when this curse 
is lifted, my people can do something 
for yours in return.
`,vd=`72
I shouldn't have boasted so much about 
Kurast on the journey here. Oh... Much 
has changed since I left.
`,Hd=`99
The dockside is apparently the only 
civilized area left in Kurast.
`,bd=`88
If you are planning to carry on your 
wild ways here, you may need the 
assistance of Asheara's Iron Wolf 
mercenaries.
`,Ad=`75
Your companion, Cain, must have 
known that he would be in grave 
danger here. You are great, indeed, to 
elicit such loyalty.
`,xd=`81
Hratli seems to be the only one left here 
with any common sense. Yet how 
sensible is it to remain here?
`,Nd=`80
I went to speak with old Alkor, but I 
disturbed his studies. He doesn't seem 
to like visitors.
`,fd=`73
Trying to get information out of Ormus 
is like straining water from a rock. His 
damned riddles are almost as 
confusing as our current state of 
affairs.
`,kd=`75
That woman, Natalya, seems to be 
waiting for something important to 
happen. She's a strange one, I think.
`,Cd=`68
All through my childhood, Kurast was a 
paradise. The once perfumed air now 
reeks of putrefaction.
`,yd=`54
Hello, there. You must be a great 
adventurer to risk coming here.
 
My name's Asheara, and I lead the 
mercenary band of mages known as 
the Iron Wolves. We've been hunting 
down demons in the jungle for months, 
but no matter how many of them we 
kill, they just keep comin'. Seems this 
whole place has been overrun by evil.
 
Rumor has it that you've come here to 
help. If that's true, then I'll let you hire 
some of my mercenaries.
 
But be careful... If you piss them off, 
they can be worse than those monsters 
out in the jungle.
`,Ld=`50
Hello, there. You must be an Amazon. 
I've heard about your people... nomadic 
warriors without peer.
 
My name's Asheara, and I lead the 
mercenary band of mages known as 
the Iron Wolves. We've been hunting 
down demons in the jungle for months, 
but no matter how many of them we 
kill, they just keep comin'. Seems this 
whole place has been overrun by evil.
 
Rumor has it that you've come here to 
help. If that's true, then I'll let you hire 
some of my mercenaries.
 
But be careful... If you piss them off, 
they can be worse than those monsters 
out in the jungle.
`,Td=`66
Your skills are unique indeed. They are 
neither sorcery, nor physical, but seem 
to be a harmonious blend of the two. 
The Iron Wolves could learn much from 
your kind.
`,Sd=`160
Why fight fair, when you can hire some 
of us?
`,wd=`107
No one comes to Kurast anymore 
without good reason.  You must be 
seeking fame and fortune.
`,Dd=`137
The Iron Wolves and I have made a 
good living around here lately.
`,Pd=`110
The jungle can take you down fast. Try 
to avoid getting trapped out there if 
you can.
`,Id=`90
Hratli may be a bit too clever for his 
own good. Still, I'd trust his work 
anytime.
`,Ed=`77
Hratli thinks he's so funny. The other 
day he said, 'Asheara, I don't recognize 
you without that big gash on your 
face.'
`,Rd=`97
Meshif says he used to live here. I'm 
surprised he came back. I'll bet he 
wishes he hadn't.
`,Bd=`78
I invited Natalya to join the Iron Wolves 
and she began lecturing me about the 
'dangers of magic'. Who the hell does 
she think she is, anyway?
`,qd=`61
Damn it, I wish you people would just 
leave me alone! I...
 
Oh, you're new here, aren't you?
 
I am Alkor, the Alchemist. I dabble in 
potions and salves, and I can sell you 
some if you really need them.
 
But don't make a habit of coming here. I 
don't like to be disturbed while I'm 
studying!
`,Gd=`48
Damn it, I wish you people would just 
leave me alone! I...
 
Oh, you're a Necromancer, aren't you? 
I've heard that your kind use powerful 
potions and such to wake the dead and 
control spirits. I'd love to discuss what 
components you use some time.
 
I am Alkor, the Alchemist. I dabble in 
potions and salves, myself, and I can 
sell you some if you really need them.
 
...Feel free to drop by anytime.
`,Ud=`55
Even I can tell that the evil in the jungle 
is growing. I hope you survive out 
there, my pasty friend. I'd still like to 
discuss what components are best 
used in necromantic potions.
`,Od=`151
Care to take a gander at my Grimoire?
`,zd=`90
I've never claimed that you'd live forever 
after trying one of my potions! Merely 
that you might look as though you had.
`,Fd=`105
I keep a library of tomes - heretical, 
exegetical, hermeneutical and 
pharmaceutical.
`,Wd=`50
There was a very fat man here recently 
asking after the Golden Bird of Ku 
Y'Leh. Have you heard of it? He kept 
muttering about ashes. I would imagine 
one Golden Bird's ash-hole to be about 
the same as another, wouldn't you?
`,jd=`150
I hope you don't object to my badgering 
the witless.
`,_d=`115
You came here with Meshif? That old 
'tour-guide to the stupid'!
 
I'm surprised you made it here in one 
piece.
`,Vd=`98
Oh, Asheara's a good customer. She 
buys a potion of manliness from me 
every week.
`,Jd=`82
Hratli's only good for making his silly 
magic weapons. It's not like he's got 
the stones to actually go out and use 
them on anything.
`,Qd=`88
Oh, Ormus has been talking in riddles 
for years. I think he does it to cover up 
the fact that he's got nothing 
intelligent to say.
`,Kd=`52
Yes, Natalya is a cute girl. However, I 
think she could use a special potion.
 
Let me see here, 'Radiant Beauty'... No. 
'Ray of Sunshine'... No, that's not it.
 
Ah, here it is: 'Relax Frosty Bitch'. This 
should help her out.
`,Yd=`38
You now speak to Ormus.
 
He was once a great mage, but now 
lives like a rat in a sinking vessel. You 
have questions for Ormus and doubt in 
yourself. Ormus sees a strange 
dichotomy in you... as he does in all 
would-be heroes.
 
Speak to him and he may grant you 
wisdom in turn. Or turn from him and 
seek wisdom in thyself.
`,Xd=`37
You now speak to Ormus, good Paladin.
 
He was once a great mage, but now 
lives like a rat in a sinking vessel. You 
have questions for Ormus and doubt in 
yourself. Ormus sees a strange 
dichotomy in you... as he does in all 
would-be heroes.
 
Speak to him and he may grant you 
wisdom in turn. Or turn from him and 
seek wisdom in thyself.
`,$d=`68
The Church which you serve is 
corrupted by evil. Yet the holy 
disciplines it taught you may yet save 
us all.
 
This is a strange time for heroes, 
Ormus thinks.
`,Zd=`65
Your salvation can only be reached 
through Hatred. A strange fate, but a 
true one.
`,eu=`52
How does one destroy Destruction? How 
does one force Terror to flee in fear? 
You have great tasks ahead of you, 
Ormus thinks.
`,au=`72
The Church of Light harbors the darkest 
shadow of all. Tread lightly.
`,ru=`89
When speaking of the dead, it is best to 
remain cryptic.
`,iu=`84
The Travincal can be breached by the 
loss of one's wits, not by the use of 
them.
`,nu=`95
Alkor is able to explain things much 
more clearly than Ormus.
`,lu=`58
For one who spends so much time away 
from home, Meshif has taken Kurast's 
corruption the hardest.
`,tu=`91
Asheara is both proud and 
self-conscious of her womanhood.
`,ou=`65
Deckard Cain... Ormus has no time for 
the last son of the Horadrim. Pride led 
that holy Order to failure.
`,su=`63
Hratli suspects that Ormus is a mage. 
He can suspect whatever he wants, 
Ormus will not show him the true 
magic.
`,cu=`53
Back in Lut Gholein Meshif told me he 
had a fondness for jade figurines. On 
his trading voyages he collected an odd 
assortment of such small statues.
 
I would show him your figurine. 
`,mu=`160
Only Deckard Cain can make sense of 
this.
`,pu=`73
Praise you! That jade figurine will 
complete the set I was collecting.
 
Here! I've had this statuette of a golden 
bird for years, but I consider it a fair 
exchange.
`,du=`89
I'm having fun just watching you run 
from place to place searching for a 
Golden Bird. Some hero you are.
`,uu=`47
I've read legends about a sage named 
Ku Y'leh, who studied the mysteries of 
life beyond death.
 
If I remember correctly, his ashes were 
ensconced within a golden statuette. It 
was a very strange tale.
`,gu=`134
You will have to take Ku Y'leh's ashes to 
Alkor.
`,Mu=`96
Such a beautiful statuette... But, you'd 
think it would've been better cared for. 
There's a compartment here that's full 
o' dust.
`,hu=`73
Ah, the Golden Bird of Ku Y'leh.  Thank 
you, my friend. 
 
Busy yourself while I experiment with 
the ashes within it. Then, return and 
see what I have made for you.
`,vu=`51
Ku Y'leh, in searching for immortal 
youth, found only an early death. His 
apprentices, seeking to live forever, 
burned his body in order to derive 
benefit from his ashes.
`,Hu=`50
Ku Y'leh was a powerful sage who was 
rumored to have brewed a potion of 
immortality. In an ironic twist of fate, 
he was murdered before his potent 
elixir could take effect.
`,bu=`78
Don't tell me you believe in all of that 
'life after death' nonsense. You should 
be more concerned with avoiding death 
than making plans for after it finds 
you.
`,Au=`120
From the ashes of Ku Y'leh I have mixed 
for you a potion.
`,xu=`94
Immortality is definitely not for me.
 
Can you imagine having to wake up 
every night just to piss for the next 
thousand years?
`,Nu=`63
So, Meshif had the Golden Bird all 
along. I wonder if he knows what he 
gave up for that jade figurine.
`,fu=`54
Ormus remembers the tale of Ku Y'leh. 
That venerable sage forgot that there 
is no life beyond death. There is only 
life.
 
Once prolonged unnaturally, it can 
become a living hell.
`,ku=`67
I must admit, your foolish quest made 
little sense to me. But now I see the 
value of your actions. I believe you do 
possess great wisdom.
`,Cu=`33
Never forget that your ultimate purpose 
here in Kurast is to destroy Mephisto. 
The ancient Horadrim imprisoned the 
Lord of Hatred inside the Guardian 
Tower that is located within the Temple 
City of Travincal.
 
Know this, friend. The only way to gain 
entry to Mephisto's prison is to destroy 
the artifact known as the Compelling 
Orb.
 
Mephisto used this device to control the 
Zakarum Priests and their followers. 
The Orb can only be destroyed with an 
ancient flail imbued with the spirit of 
the one incorruptible priest.
 
Soon after his imprisonment, Mephisto 
worked his evil corruption on the 
Zakarum priesthood. All were turned to 
his dark ways, save one - Khalim, the 
Que-Hegan of the High Council.
 
Mephisto directed the other Council 
priests to slay and dismember Khalim 
and then scatter his remains across 
the Kingdom. The Priest Sankekur 
succeeded Khalim as Que-Hegan, 
eventually becoming the embodiment of 
Mephisto here on the mortal plane.
 
The corrupted High Council fashioned 
an Orb to control the rest of the 
Zakarum faithful and used their powers 
to hide the lair of their master from 
mortals.
 
Your task is to collect the scattered 
relics of Khalim - his Heart, his Brain, 
and his Eye. Then, using the Horadric 
Cube, transmute Khalim's Flail with his 
relics.
 
Once this is accomplished, you must 
destroy the Compelling Orb with 
Khalim's Will to open the way into the 
corrupt sanctum of Mephisto.
`,yu=`61
You have found Khalim's Heart, and it 
still bears the courage to face 
Mephisto!
 
Place it in the Horadric Cube along with 
Khalim's other relics - the Eye, the 
Brain, and the Flail.
`,Lu=`52
Ahh... Khalim's Eye! Only it can reveal 
the true path to Mephisto.
 
Place the Eye in the Horadric Cube 
along with Khalim's other relics - the 
Heart, the Brain, and the Flail.
`,Tu=`58
This is most fortunate! Khalim's Brain 
knows Mephisto's weakness.
 
Place it in the Horadric Cube along with 
Khalim's other relics - the Eye, the 
Heart, and the Flail.
`,Su=`46
Once properly imbued, Khalim's Flail can 
destroy the Compelling Orb and reveal 
the way to Mephisto.
 
Place it into the Horadric Cube along 
with Khalim's relics - his Heart, his 
Brain, and his Eye. Then, transmute 
them to carry out Khalim's Will.
`,wu=`54
Masterfully done, hero! You have 
crafted Khalim's Will. Employ it to 
destroy the Compelling Orb and open 
the way to Mephisto. 
 
May the true Light guide your way.
`,Du=`56
It pains me to waste time with you, so 
I'll get right to the point.
 
There is a very special book which you 
must find for me. It was written long 
ago by a sage known as Lam Esen, who 
studied Skatsimi magic and the effects 
of the Prime Evils on the mortal world. 
The Black Book was lost when the 
Children of Zakarum took over this 
land.
 
Now, you must reclaim it without delay! 
Its knowledge may aid us in this dark 
time ahead.
`,Pu=`73
The Black Book contains powerful 
secrets of Skatsim, the Old Religion, 
long eclipsed by Zakarum.
 
I should warn you. The Black Book is 
much sought after by both good and 
evil. Be wary.
`,Iu=`62
The Children of Zakarum believe that 
the Black Book is filled with 
blasphemous heresy. In truth, the book 
may contain the secrets to our ultimate 
redemption.
`,Eu=`73
Oh. No one really believes that the Black 
Book exists. It's just a symbol of 
Zakarum's anti-Skatsim propaganda.
`,Ru=`102
Many things can be found in the city of 
Kurast. The book may be there.
`,Bu=`54
We have long sought the Black Book of 
Lam Esen. Rumors of its whereabouts 
spread as fast as jungle plagues. If you 
find it, take it to Alkor.
`,qu=`72
The Black Book is a powerful source of 
information. The Zakarum will do 
everything in their power to stop you 
from obtaining it.
`,Gu=`81
I've heard of the Black Book. My Order's 
code is based on many of its passages. 
If you find it, I will be greatly 
impressed.
`,Uu=`104
Did I neglect to mention that the book 
contains useful information about the 
Prime Evils?
`,Ou=`55
Even if you find the sacred Book, you 
must still traverse the jungle of 
meaning within it. That journey could 
prove to be far more perilous.
`,zu=`56
Kurast was once the greatest city in the 
world. Now it is hard to tell where the 
jungle stops and the city begins. The 
jungle grows rampant on the soil 
enriched by the blood of my fellow 
citizens.
`,Fu=`68
I believe I can trust you now.
 
When you first arrived, I suspected you 
a spy for the Zakarum, the false 
religion whose faithful are now under 
the sway of a mysterious power. 
They've made a mockery of the Old 
Religion of Skatsim.
`,Wu=`62
Not getting much help?
 
You know, people are like rugs. Hang 
them out a window and shake 'em a 
couple times. You'll be surprised how 
much dirt comes out.
`,ju=`81
I heard that there are ruined temples in 
Kurast. Perhaps you will find the Black 
Book in one of them.
`,_u=`105
I hope you find the Black Book soon. I 
could use something to read while I 
wait for my orders.
`,Vu=`83
You have found the Book! It should give 
all of us here some insight into the 
nature of the Prime Evils...
 
Ah, but as for you...
`,Ju=`70
Why is the Black Book of Lam Esen like 
a coffin? Simple. Each holds the shape 
of our future.
`,Qu=`75
Thank all that's holy. You've returned 
with the Black Book! Maybe now you 
can put an end to the Evil that has 
destroyed my homeland.
`,Ku=`135
The Iron Wolves are very impressed by 
your skills.
`,Yu=`74
We have the Book. Now we must see if 
we can bear its revelations.
`,Xu=`86
You have found a source of information 
powerful enough to turn the tide 
against the Zakarum.
`,$u=`89
So, you've returned with the Book. You 
surprise me. You must be very 
resourceful.
`,Zu=`45
As I told you before, I placed an 
enchantment upon the dockside in 
order to keep the demons at bay. But 
lately, the enchantment seems to be 
weakening.
 
If memory serves me correctly, there is 
a holy Skatsimi blade that could 
revitalize the enchantment. The blade 
is called the Gidbinn.
 
Find it, and our sanctuary here will 
remain safe.
`,e3=`66
Have you not heard of the Gidbinn? 
Well, allow me to reduce your 
ignorance on the subject.
 
The Gidbinn is an enchanted dagger - a 
religious artifact greatly valued by the 
Old Religion, Skatsim.
`,a3=`64
Ormus is familiar with the Gidbinn. But 
how would a powerful Skatsimi artifact 
aid an unbeliever like you?
`,r3=`66
The Gidbinn is one of the few remaining 
relics of Skatsim, the Old Religion. It is 
reputed to have great powers.
`,i3=`107
The Gidbinn will reinforce the 
enchantments that protect the 
dockside from the evil that infests 
Kurast.
`,n3=`54
As far as we know, the Gidbinn is in the 
possession of the Children of Light. 
They do not wish it to fall into the 
hands of those who can restore its 
powers.
 
You may not believe it, but Ormus is the 
one who can use the Gidbinn to protect 
us.
`,l3=`55
I've done some research on the Taan 
mage-clan, and it seems that most of 
their magical studies were focused on 
Skatsimi rites.
 
If anyone is qualified to use the powers 
of the Gidbinn, it would be Ormus.
`,t3=`73
Don't let the Gidbinn's size fool you. 
Though it is only a small dagger, it 
holds tremendous power when in the 
hands of a true Skatsimi mage.
`,o3=`70
Legend has it that the Skatsimi priests 
placed great power within the small 
blade. Power enough to repel this 
terrible jungle-curse which encroaches 
on our sanctuary.
`,s3=`83
If we are to have peace from the 
shadow, you must find the weapon 
which will destroy the Light.
`,c3=`67
The jungle is like nothing you've ever 
seen before. Imagine Paradise 
festering like a wound... then bursting!
`,m3=`145
I'm certain that the Gidbinn is very 
closely guarded.
`,p3=`70
Once the Gidbinn is found, Ormus will 
use it to strengthen the protective 
barrier around the dockside.
`,d3=`75
Since you haven't come across the 
Gidbinn yet, the dagger must be deeper 
in the jungle nearer Kurast.
`,u3=`97
You'd best get back out there and find 
that blade. The jungle creeps further 
into this camp by the hour.
`,g3=`77
Hah! You have stolen the fabled blade 
from right under Zakarum's nose! This 
is a great day, indeed!
`,M3=`41
You have done well, noble hero. Ormus 
congratulates you. The old spirits of 
Skatsim will watch over you for 
returning their sacred blade.
 
Now, after all these years, Ormus will 
once again use his powers to protect 
the innocent from the shadow. The 
spell that protects the dockside shall 
now be reinforced.
`,h3=`79
With any luck, the spirits of Skatsim will 
grant us revenge upon the powers that 
ravaged this land.
`,v3=`99
Now that fewer of the Iron Wolves are 
needed to guard the dockside, some of 
them have volunteered to accompany 
you free of charge.
`,H3=`80
The Gidbinn's magic can only be 
channeled through Ormus.
 
Take it to him. He has the necessary 
knowledge about the ancient Skatsimi 
magics.
`,b3=`62
Who could have foreseen that the Old 
Religion would play such an effective 
role in our war against the Three? 
Again, your efforts amaze me, my 
friend.
`,A3=`67
You are truly amazing, stranger. There 
are precious few items in the world 
that would tempt me to go up against 
the Children of Zakarum and their 
midget minions.
`,x3=`101
This magic ring does me no good.
 
Here... Wear it proudly!
`,N3=`36
You have done well, my friend. Your 
courage and valor are an inspiration to 
us all.
 
But now the time has come to face 
those responsible for the evil that has 
stifled our land. You must destroy the 
High Council of Zakarum!
 
Long ago, these elders were charged 
with the stewardship of Mephisto, the 
Lord of Hatred, who was imprisoned 
within the Guardian Tower.
 
Through the generations, these pious 
men slowly fell more and more under 
the sway of Mephisto's malevolent 
power and the Council became an evil 
mockery of its former glory. 
 
It is Mephisto's Hatred that has 
corrupted Zakarum and turned its 
devout followers into paranoid 
fanatics. That is why you must travel 
to the Temple City of Travincal and 
slay the Council.
 
Once they are gone, Mephisto's hold 
over this land and its people will be 
broken!
`,f3=`84
The Black Book contains some vague 
prophecies regarding this undertaking. 
I'm not so sure it will turn out well for 
you.
`,k3=`90
I am but a potion dealer and an avid 
reader of occult books. What do I know 
of the Travincal?
`,C3=`54
You must know that the Guardian Tower 
in the Temple City was built by the 
Horadrim for one purpose - to hold 
Mephisto. Once the Council is dead, 
you may enter the Tower.
`,y3=`54
You must know that the Guardian Tower 
in the Temple City was built by the 
Horadrim for one purpose -  to hold 
Mephisto. Once the Council is dead, 
you may enter the Tower.
`,L3=`68
There is only one way to the Temple 
City. You will have to cross many rivers 
and streams, but you'll find it. A great 
tower stands at its center.
`,T3=`113
It has been said that Ormus speaks 
most clearly when his ideas are utterly 
mad.
`,S3=`89
The Children of Zakarum who guard the 
Tower square can be killed, but their 
numbers are vast. You must destroy 
their Council.
`,w3=`105
There are many zealots among the 
followers of Zakarum. It will be difficult 
to get past them.
`,D3=`104
Remember. You can always find 
sanctuary here with us.
`,P3=`75
This has been a trying time for all of us, 
but I sense this nightmare is coming to 
an end.
`,I3=`63
Ormus tells me that the Council is 
comprised of tremendously powerful 
priests. It will be difficult to best them.
`,E3=`93
The Temple City is well guarded. You'd 
best keep your wits about you.
`,R3=`100
You are incredibly brave to venture into 
the lion's den. I wish you luck.
`,B3=`95
Beware the followers of Zakarum. Their 
fanaticism is their greatest weapon.
`,q3=`111
Kill as many as you can. I have a 
morbid love of excess.
`,G3=`91
If only we could have found the Black 
Book. I feel as though a malevolent 
hand has led us away from it.
`,U3=`49
If you die on this quest, I will 
commemorate your sacrifice in an epic 
poem. You will not need a potion to 
achieve immortality. Ormus' words will 
do that.
`,O3=`110
Within the Temple City is a courtyard. 
The Council resides there.
`,z3=`107
I have heard rumors that the Prime 
Evils are here seeking their Brother.
`,F3=`161
The Iron Wolves and I are at the ready 
to aid you.
`,W3=`139
Things are getting wilder than Ladies 
Night at the Slippery Fist.
`,j3=`65
The followers of Zakarum demand 
complete allegiance to their creed. 
They have slaughtered many of their 
own for minor grievances.
 
They will not hesitate to kill you.
`,_3=`75
After having served Mephisto all these 
years, the Council must be twisted by 
hatred and evil.
`,V3=`81
Sankekur may be using a Compelling 
Orb to control the minds of the 
Children of Zakarum.
`,J3=`80
I respect your need to do this. Honor 
demands that you see this through. Yet 
your chances are so slim...
`,Q3=`80
I respect your need to do this. Honor 
demands that you see this through. Yet 
your chances are so slim...
`,K3=`91
You've accomplished the impossible! By 
killing the Council, the curse of 
Zakarum will be lifted and our land will 
be free!
 
Oh. Thank you!
`,Y3=`40
Ormus is grateful to you, stranger. You 
have broken the long, dark reign of 
Zakarum and delivered the first 
paralyzing blow against the Three.
 
Yet still, the true test lies ahead. For he 
whom the Council guarded still lives 
within the Blackened Tower.
`,X3=`76
It seems the jungle is already dying 
back. You've broken the curse, my 
friend! May the Light bless you!
`,$3=`125
The sun has set on the Religion of Light.
`,Z3=`68
The followers of Zakarum lacked all 
sense of moderation. The collapse of 
their tainted religion gives me hope.
`,eg=`48
Ridding Kurast of the Council of 
Zakarum was essential. Still, there is 
more you must do. The Compelling Orb, 
too, must be destroyed.
 
Diablo and Baal must be close to finding 
their brother, Mephisto, by now. You've 
no time to waste.
`,ag=`88
I can hardly believe you did it. Your 
power blankets you like a shining aura.
`,rg=`53
Diablo and Baal have surely found the 
Temple City by now. They seek to free 
their Brother, Mephisto, who was 
imprisoned by the Horadrim in the 
Temple's Guardian Tower.
 
You must reach him before his Brothers 
do and prevent them from releasing 
Hatred upon the world.
`,ig=`90
The hidden ways of the Tower are long 
forgotten. Though... it is rumored to 
have been built as far below the 
ground as above it.
`,ng=`114
We have seen Diablo, but remain unsure 
of his Brothers' whereabouts.
`,lg=`52
Make haste! Though the Three are sure 
to reunite, it is uncertain as to what 
they have planned once they do.
 
Be cautious, my friend. Though you are 
mighty, no mortal can stand alone 
against the power of the Prime Evils.
`,tg=`52
Make haste! Though the Three are sure 
to reunite, it is uncertain as to what 
they have planned once they do.
 
Be cautious, my friend. Though you are 
mighty, no mortal can stand alone 
against the power of the Prime Evils.
`,og=`66
Be careful when you return to the 
Tower. Though many of the followers 
of Zakarum have fled, there's no telling 
what horrors still lurk inside it.
`,sg=`116
Move quickly, my friend, and end this 
curse once and for all!
`,cg=`60
I sent a few of my Iron Wolves on a 
scouting mission into the jungle near 
the Temple City... They encountered 
two cloaked men who attacked them 
with horrifying powers.
 
My men barely survived. I have to 
assume that the two strangers are 
Diablo and Baal.
 
You'd better hurry. They're close to 
finding their brother.
`,mg=`93
Many Iron Wolves have disappeared in 
Travincal. The Evil is still strong there.
`,pg=`43
Mephisto, along with Baal, was 
originally captured in the desert near 
Lut Gholein. But imprisoning two of the 
Brothers together was far too 
dangerous.
 
The Horadrim built the Guardian Tower 
to hold Mephisto. When Zakarum came 
to power in this land, it took over the 
Temple City without paying any heed to 
what was locked within the Tower.
 
And it became their doom.
`,dg=`73
I hear there is a little family reunion 
about to take place in Kurast. The 
Three brothers draw close.
`,ug=`116
You must reach Mephisto before his 
brothers do.
`,gg=`50
The ancient Horadrim always feared 
that the Three would escape their 
prisons and unite. I can't believe that I, 
the last of their Order, have seen it 
come to pass.
 
You are the only one who can prevent 
this, my friend. The final hour draws 
near.
`,Mg=`75
Now you rush to face Mephisto. Don't 
give in to your hatred. That is his 
greatest weapon against you.
`,hg=`75
Now you rush to face Mephisto. Don't 
give in to your hatred. That is his 
greatest weapon against you.
`,vg=`68
Well, the good news is that events are 
unfolding just as Lam Esen foretold. 
The bad news is that the story ends in 
our utter ruin!
`,Hg=`80
I'm afraid both fear and a large dose of 
elixir preclude me from answering.
`,bg=`59
I understand that the great Patriarch of 
Zakarum, Sankekur, now embodies 
Mephisto.
 
You must overcome Hatred lest Terror 
and Destruction claim us all!
`,Ag=`77
I am loath to describe what will happen 
if Diablo and Baal release Mephisto.
`,xg=`110
I ought to return to the ship. We may 
have to sail from here very quickly.
`,Ng=`110
I ought to return to the ship. We may 
have to sail from here very quickly.
`,fg=`80
The sudden reduction in our ranks 
makes us eager to destroy Diablo and 
his brothers. Vengeance for the Iron 
Wolves!
`,kg=`200
We will fight to the death.
`,Cg=`58
Why build a Tower to place the beast 
below ground? At times I believe the 
Horadrim lacked common sense.
`,yg=`106
Shouldn't you be running frantically up 
and down stairs about now?
`,Lg=`96
Search the Tower thoroughly. Mephisto 
must not escape.
`,Tg=`96
Search the Tower thoroughly. Mephisto 
must not escape.
`,Sg=`55
Beware, my friend. Sankekur may be the 
most powerful mortal in the world. He 
controls thousands of fanatical 
worshippers and embodies the Lord of 
Hatred, himself. His death will be no 
easy task.
`,wg=`55
Beware, my friend. Sankekur may be the 
most powerful mortal in the world. He 
controls thousands of fanatical 
worshippers and embodies the Lord of 
Hatred himself. His death will be no 
easy task.
`,Dg=`71
Your news is great indeed. You have 
saved us all. I would smile, but I'm 
afraid my face might collapse.
`,Pg=`48
You have defeated a Prime Evil in 
combat. Ormus is impressed beyond 
words. But staying here will not end 
this conflict.
 
You must enter the Infernal Gate and 
stop Diablo once and for all.
`,Ig=`70
Ahh... Now, Kurast can begin the task 
of rekindling its former glory... I thank 
you.
`,Eg=`65
Well done, my friend. You are a great 
champion of Order. Please, consider 
yourself an honorary Iron Wolf.
`,Rg=`121
It looks like you're going to Hell before 
me.
 
Put in a good word.
`,Bg=`42
Our faith in you was well deserved. But 
Diablo has made his way to Hell; and it 
is likely that Baal followed him there.
 
Enter the Infernal Gate and kill the Lord 
of Terror before all is lost. Only then 
will our world be saved!
`,qg=`55
Word is spreading fast that you killed 
Mephisto. I'd be honored to fight 
beside you in Hell, but I've just received 
my mission orders.
 
I'll be travelling to the Barbarian lands 
of the North, but I can't tell you why. 
With luck, our paths will cross again. 
Farewell.
`,Gg=`43
It is good to see you again, hero.
 
Mephisto's defeat is a great victory for 
the Light. I knew that you would 
eventually find your way here. The 
Pandemonium Fortress is the last 
bastion of Heaven's power before the 
Gates of the Burning Hells.
 
This place has been hallowed by the 
blood of thousands of champions of 
the Light, many of whom were mortal, 
like yourself. Now the final battle 
against the Prime Evils draws near... 
and you must face it alone. 
 
I have been forbidden to aid you 
directly, save for a few bits of wisdom. 
For this is the hour of mortal Man's 
triumph...your triumph.
 
May the Light protect you and the 
powers of Heaven shine upon your 
path...
`,Ug=`62
Long ago, I swore an oath to watch 
over the Horadrim and their 
descendants.
 
As Deckard Cain is the last of their 
esteemed Order, I will not allow him to 
perish here so far from the lands of his 
birth.
 
Be at ease, hero, I know that he is your 
friend. He shall come to no harm.
`,Og=`41
Can you believe this place? Did you ever 
dare to dream that you'd one day 
stand upon the crossroads between 
Heaven and Hell? This Pandemonium 
Fortress is truly miraculous.
 
However, your journey is not yet over. 
Diablo still roams free in Hell, 
marshalling his demonic forces. Only 
when he is beaten will our world finally 
have peace.
 
Hurry now... the sands of time slow for 
no one! 
`,zg=`48
I have read much about the enigmatic 
Archangel Tyrael. He was revered in 
Horadrim lore both for his compassion 
for mortals and his unquenchable 
spirit.
 
It was rumored that he went against the 
wishes of Heaven and gave the 
Horadrim the original Soulstones in 
order to trap Diablo and his Brothers.
`,Fg=`72
Halt! Before venturing into Diablo's lair, 
go to the Hellforge with Mephisto's 
Soulstone.
 
Place the stone on the Hellforge and 
use the Hellforge Hammer to destroy 
it.
`,Wg=`66
Proceed, hero, into Terror's lair.
 
Know that Diablo's innermost sanctum 
is hidden by five seals.
 
Only by opening each of these seals can 
you clear your way to the final battle.
`,jg=`42
There is a dark, tortured soul who was 
trapped within this forsaken realm long 
ago. He was called Izual by mortal 
men, and in ages past he was my most 
trusted Lieutenant.
 
Yet, against my wishes he led an 
ill-fated assault upon the fiery 
Hellforge, itself.
 
Despite his valor and strength, Izual 
was captured by the Prime Evils and 
twisted by their perverse power. They 
forced him to betray his own kind and 
give up Heaven's most guarded 
secrets.
 
He became a corrupt shadow of his 
former self - a fallen angel trusted 
neither by Heaven nor Hell.
 
For his transgressions, Izual's spirit 
was bound within the form of a terrible 
creature which was summoned from 
the Abyss. His maddened spirit has 
resided within that tortured husk for 
many ages now.
 
It seems to me that he has suffered 
long enough. I implore you, hero, find 
Izual and release him from his cruel 
imprisonment.
 
Put an end to his guilt and suffering.
`,_g=`59
Though Izual no longer carries the 
Angelic Runeblade, Azurewrath, he may 
still possess great strength and power 
within his new form.
 
Also, he may not be able to tell friend 
from foe while in his present state. If 
you find him, he will almost certainly be 
hostile.
 
Proceed with the utmost caution.
`,Vg=`54
Tyrael has asked you to confront Izual 
the Fallen? He must have great faith in 
your abilities!
 
I trust you know what you're doing... Be 
careful. You're our last hope.
`,Jg=`75
You mustn't delay, mortal hero. Izual 
must be put to rest, but Diablo still 
lurks within this realm.
 
Go now... Hurry!
`,Qg=`83
Having trouble finding the Fallen Angel, 
eh?
 
You'd better hurry. It's beginning to feel 
like some great evil is permeating the 
air around here.
`,Kg=`47
Tyrael was a fool to have trusted me!
 
You see, it was I who told Diablo and his 
Brothers about the Soulstones and how 
to corrupt them. It was I who helped 
the Prime Evils mastermind their own 
exile to your world.
 
The plan we set in motion so long ago 
cannot be stopped by any mortal 
agency.  Hell, itself, is poised to spill 
forth into your world like a tidal wave 
of blood and nightmares.
 
You and all your kind... are doomed.
`,Yg=`53
Thank you, hero, for putting Izual's 
tortured spirit to rest. May the Light 
protect you and the powers of Heaven 
shine upon your path.
 
But, if what you tell me is true, then I 
fear that we have been played for fools 
all along.
 
Izual helped Diablo and his Brothers 
trick me into using the Soulstones 
against them... Now the Stones' powers 
are corrupted.
 
With the combined powers of the 
Soulstones under their control, the 
Prime Evils will be able to turn the 
mortal world into a permanent outpost 
of Hell!
`,Xg=`68
You're lucky to be alive, my friend! It is 
imperative that you find and stop 
Diablo!
 
You should speak of this with Tyrael. He 
will know what to make of this.
`,$g=`53
The time has come for you to destroy 
Mephisto's Soulstone!
 
Take the Stone to the Hellforge. Place it 
upon the forge and strike it soundly 
with the Hammer.
 
Only by doing this can you prevent 
Mephisto from manifesting in this 
world ever again.
`,Zg=`50
The time has come to destroy 
Mephisto's Soulstone! 
 
Although I picked it up before entering 
the Infernal Gate, I believe you should 
carry out this crucial mission.
 
Take the Stone to the Hellforge.  Place 
it upon the forge and strike it soundly 
with the Hammer.
 
Only by doing this can you prevent 
Mephisto from manifesting in this 
world ever again.
`,eM=`70
Congratulations, hero!
 
Surely, even Diablo, himself, sensed the 
fury unleashed when you smashed his 
Brother's Soulstone.
`,aM=`48
The time has come to hunt down and 
destroy Diablo, himself.
 
But beware, the Lord of Terror is not to 
be underestimated. He single-handedly 
destroyed the town of Tristram and 
corrupted the last noble hero who tried 
to stop him.
 
This time, you must defeat him for 
good. Only by destroying the Soulstone 
which he carries will his spirit be 
banished forever.
 
Good luck! Though this be our darkest 
hour, it may yet be your greatest 
moment.
`,rM=`54
You don't have time to dally about here!
 
Diablo awaits you in Hell. Remember... 
Diablo's greatest weapon against you is 
Terror.
 
Don't give in to your fears. Resist his 
power and put an end to him for good!
`,iM=`48
The time has come to hunt down and 
destroy Diablo, himself.
 
But beware, the Lord of Terror is not to 
be underestimated. He single-handedly 
destroyed the town of Tristram and 
corrupted the last noble hero who tried 
to stop him.
 
This time, you must defeat him for 
good. Only by destroying the Soulstone 
which he carries will his spirit be 
banished forever.
 
Good luck! Though this be our darkest 
hour, it may yet be your greatest 
moment.
`,nM=`62
Praise be to the Light! You have 
accomplished the impossible!
 
Diablo and Mephisto have been 
banished back into the Black Abyss 
that spawned them and the corrupted 
Soulstones are no more.
 
You've done well, hero. For now, you 
should rejoice.
`,lM=`42
I knew there was great potential in you, 
my friend. You've done a fantastic job.
 
Though my ancestors often struggled 
against the Three Evils and their 
minions, I've always lived a shut-in, 
scholarly life. I'm glad that my wisdom 
aided you.
 
Now, I wish to leave this place. Though 
Heaven's Gates are a marvel to behold, 
I hope I won't have to see them again 
for many, many years.
`,tM="CHAT HELP",oM="CHAT COMMANDS",sM="To select a Character, left-click on the Character portrait to highlight it with an aura. To deselect any highlighted character, left-click on their portrait.",cM="The buttons located under the Chat Window on the left side of the screen have the following functions:",mM="SEND displays your message to everyone in your chat Channel, regardless of what character portrait is currently selected. This button is activated as soon as you start typing in the Text Box.",pM="WHISPER sends your message only to the character that you have selected. This button is activated as soon as you start typing in the Text Box and have another character selected.",dM="SQUELCH filters out incoming messages from the character that you have selected. Characters that you have squelched are marked with a red X graphic. This button is activated as soon as you select another character.",uM="UNSQUELCH allows you to again receive incoming messages from a character that has been squelched.",gM="EMOTE lets you perform an action that the whole room can <see> as represented through text.",MM="For example, if Doomhammer wants to greet all the players in the chat Channel, he could type, <waves hello.> and then click the EMOTE button. Everyone in the Channel will then receive the message, <Doomhammer waves hello.> This button is activated as soon as you start typing in the Text Box.",hM="\xFFc5Gray Text\xFFc4 indicates when someone Joins or Leaves the chat Channel.",vM="\xFFc7Gold Text\xFFc4 indicates the name of the player speaking.",HM="\xFFc0White Text\xFFc4 indicates what you or others have said out loud to the entire chat Channel.",bM="\xFFc2Green Text\xFFc4 indicates what you have <whispered> to a specific person, or any message that has been <whispered> to you, in the chat Channel.",AM="\xFFc3Blue Text\xFFc4 represents actions that have been taken by people in the chat Channel.",xM="\xFFc1Red Text\xFFc4 represents error messages sent directly from battle.net.",NM="THE DIALOGUE WINDOW",fM="This window on the right side of the screen is used to display and enter both game and profile information. Unlike the Chat Window, this area changes depending on what function you have activated. The buttons for these functions are discussed in detail in the following section:",kM="CREATE",CM="Lets you form a new game for other players to join. There are several choices listed below that you need to make when creating a new game, although many of them are optional.",yM="Game Name is how you want your game to be displayed in the Join Game screen. It can be cryptic or descriptive, although certain words and names are restricted.",LM="Password gives you the option to make your game Private. Other players who wish to join your game will need to know the password you have selected.",TM="Game Description lets you say something about the game you are forming. This is a good way to advertise for the kind of player or character you want to join your game.",SM="Maximum Number of Players sets a limit as to how many characters can be in your game at any one time. The default setting is 4. You can change the number of players, up to a maximum of 8, by clicking the Up or Down arrows next to the box.",wM="Character Difference sets a range above and below the level of your character that other characters joining your game must fall into. The default setting is set at 4 to determine who can join your game.",DM="To set no level restrictions, click the check box next to this option. The displayed number 4 means that any character joining your game must be within 4 levels of your character. You can change the level difference by clicking the Up or Down arrows next to the box.",PM="Normal, Nightmare and Hell sets the difficulty levels at which you can play. The default setting is Normal. Characters must meet certain requirements to start games with the Nightmare and Hell difficulties. Until those requirements are met, these options will be non-selectable.",IM="JOIN",EM="Lets you enter an existing game. Games that are listed in this screen are considered Public and can be can be joined any time they have space for a player within them.",RM="Selecting a game from this list will display information on the game, including the characters and the elapsed time of the game. To join a Private game, you will be required to enter the name of the game and its assigned password.",BM="CHANNEL",qM="Lets you join an existing chat Channel or gives you the opportunity to create a Channel of your own. To enter an established Public Channel, select one from the Channels list and click the OK button. To enter a Private Channel, you will need to enter the name of the Channel that you wish to enter.",GM="If you wish to start your own Channel, enter the name of the Channel that you wish to create in the Channel Name Field. If this channel does not exist, you will automatically create that Channel.",UM="LADDER",OM="Allows you to view your character's ranking in the Diablo II Ladders for your Realm.",zM="The STANDARD LADDER displays the top characters, ranked by experience. The default setting displays overall rankings, but you can view sorted lists after selecting the By Class option.",FM="The HARDCORE LADDER displays the top Hardcore characters, ranked by experience. The default setting displays overall rankings, but you can view sorted lists after selecting By Class option.",WM="QUIT closes the Battle.net chat interface and returns you to the Character Selection screen. Although you are still connected to Battle.net, you cannot chat or start games until you have selected a character.",jM="ADVANCED COMMANDS",_M="When using advanced commands, you may also use character names for people in the same Realm, and character names @Realm for people in another Realm.",VM="Wherever a command below calls for the use of <accountname>, please use either <charactername>, <charactername@Realm>, or <*accountname>.",JM="You can access any of these advanced features by entering the following commands in the Text Box where you normally type messages:",QM="/whisper <*accountname>, /w <*accountname>",KM="/msg <*accountname>, /m <*accountname>",YM="Sends a private message to another user on battle.net",XM="/me, /emote",$M="Allows you to perform an action in the chat room.",ZM="/squelch <*accountname>",eh="/ignore <*accountname>",ah="Allows you to ignore messages from the indicated user.",rh="/unsquelch <*accountname>",ih="/unignore <*accountname>",nh="Allows you to again receive messages from this user.",lh="/away <reason>",th="Lets other people who send you messages know that you are away from your keyboard and cannot respond. You may provide a reason for your absence, by typing it after the /away command. To turn off this auto message when you return to your keyboard, enter just /away by itself.",oh="/dnd",sh="Lets other people who send you messages know that you do not wish to be disturbed. You may provide a reason for your absence, by typing it after the /dnd command. To turn off this auto message when you return to your keyboard, enter just /dnd by itself.",ch="/channel <channelname>, /join <channelname>",mh="Takes you to the battle.net Channel of your choice. If you wanted to enter the technical support Channel, you would simply type /channel technical support. If you attempt to join a Channel that does not exist, you will automatically create that Channel.",ph="/who <channelname>",dh="Provides you with a list of the battle.net account names of the players that are currently in the requested battle.net Channel.",uh="/ban <*accountname>",gh="Bans an account from entering a private Channel and can only be issued by the Channel operator. Use /unban <accountname> to allow accounts banned from a private Channel back into that Channel.",Mh="ctrl+c, ctrl+x ctrl+v",hh="Use these commands to copy, cut, and paste highlighted text. Use ctrl+a to select all text in the text field. Use ctrl+m to toggle music off/on. Use ctrl+n to paste the account name of a selected character.",vh="/designate <*accountname>",Hh="Designates the player of your choice to become the next Channel operator, which will take effect after the current Channel operator leaves the Channel and can only be issued by the current Channel operator.",bh="/kick <*accountname>",Ah="Kicks an account from a private Channel and can only be issued by the Channel operator. The kicked player, however, can immediately rejoin the channel.",xh="/rejoin, resign",Nh="Causes a Channel operator to rejoin the Channel, appearing at the end/bottom of the list instead of the front/top of the list. Only the Channel operator can issue this command.",fh="/whois <*accountname>, /where <*accountname>",kh="/whereis <*accountname>",Ch="Searches for another player in all battle.net Public Chat channels and all Blizzard games, telling you their account name, account number and current location.",yh="/whoami",Lh="Provides you with your current account number and location on battle.net.",Th="/d2notify",Sh="Toggles battle.net Join/Leave notifications in the Chat Channel.",wh="/help, /?",Dh="Accesses the general battle.net help text.",Ph="/time",Ih="Provides you with the current battle.net time and your current Local time.",Eh="/users",Rh="Provides the number of users, games, and channels that are currently active across all of battle.net.",Bh="/stats <*accountname> <programID>",qh="Provides you with the Ladder statistics for other Blizzard games supported over battle.net. The program ID for each game is as follows; StarCraft < STAR>, Brood War <STARX>, and Warcraft II: battle.net Edition <W2BN>.",Gh="Right-clicking on your own character allows you to edit your own profile.",Uh="Using the 'Tab' key in the battle.net chat room cycles through the last 10 commands you have issued.",Oh="If you need further help, please go to the TECHNICAL SUPPORT Channel on battle.net, consult the Diablo II manual or go to the Blizzard technical support page at http://www.blizzard.com/support/",zh="BATTLE.NET COMMANDS",Fh="/whisper, /msg, /reply",Wh="/me",jh="/away",_h="/squelch, /unsquelch",Vh="/ban, /unban, /kick",Jh="/channel",Qh="/whois, /where, /whoami",Kh="/d2notify",Yh="/designate, /rejoin",Xh="/time",$h="/who, /users",Zh="/stats",e4="Travincal",a4="Harem",r4="Sewers",i4="Act 2 Prologue",n4="Radament's Lair",l4="The Horadric Staff",t4="Tainted Sun",o4="Arcane Sanctuary",s4="The Summoner",c4="The Seven Tombs",m4="Act 3 Prologue",p4="Lam Esen's Tome",d4="Khalim's Will",u4="Blade of the Old Religion",g4="The Golden Bird",M4="The Blackened Temple",h4="The Guardian",v4="Act 4 Prologue",H4="The Fallen Angel",b4="Terror's End",A4="Hell's Forge",x4="Lut Gholein",N4="Find Radament's Lair in the Lut Gholein sewers.",f4="Kill Radament.",k4="Return to Atma for a reward.",C4="Show the scroll to Cain in Lut Gholein.",y4="Search the Halls of the Dead under the Dry Hills for the Cube. Search the Maggot Lair under the Far Oasis for the Shaft. Search the Claw Viper Temple for the Headpiece.",L4="Use the Horadric Cube to restore the Staff.",T4="Take the Staff into Tal Rasha's Tomb.",S4="Take the artifacts to Cain in Lut Gholein.",w4="Look for the source of the darkness.",D4="Ask Drognan about the strange darkness.",P4="Destroy the Serpent Altar in the Claw Viper Temple beneath the Valley of Snakes.",I4="Speak with the townsfolk in Lut Gholein.",E4="Look for the Arcane Sanctuary within the Palace.",R4="Talk to Drognan.",B4="Find Horazon's Journal.",q4="Continue the search for the Seventh Tomb.",G4="Beware the Summoner.",U4="Kill the Summoner.",O4="Return to town for more information.",z4="Find Tal Rasha's Tomb.",F4="The Symbol of the True Tomb of Tal Rasha.",W4="Kill Duriel.",j4="Explore Tal Rasha'a Chamber.",_4="Talk to Jerhyn.",V4="Talk to Jerhyn.",J4="Talk to Meshif.",Q4="Jungle Village",K4="Search the six temples in the Bazaar, Upper Kurast, and the Causeway for Lam Esen's Tome.",Y4="Talk to Alkor.",X4="Find Khalim's relics. Search for his Eye in the Spider Cavern.",$4="Search for Khalim's Brain in the Flayer Dungeon.",Z4="Search for Khalim's Flail in Travincal. Beware the High Council.",ev="Search for Khalim's Heart in the Sewers under the Kurast Bazaar.",av="Transmute Khalim's relics - the Flail, Eye, Heart, and Brain - with the Horadric Cube.",rv="Use Khalim's Will to smash the Compelling Orb.",iv="Ask Cain about Khalim's relics.",nv="Look for the Gidbinn in the Flayer Jungle.",lv="Pick up the Gidbinn.",tv="Return the Gidbinn to Ormus.",ov="Talk to Asheara.",sv="Talk to Ormus.",cv="Ask Cain about the Jade Figurine.",mv="Show Meshif the Figurine.",pv="Ask Cain about the Golden Bird.",dv="Give the Golden Bird to Alkor.",uv="Return to Alkor for reward.",gv="Find the Blackened Temple within Travincal.",Mv="Kill the High Council.",hv="Ask Cain for help.",vv="Smash the Compelling Orb with Khalim's Will to open the way to Mephisto's Durance.",Hv="Search for Mephisto in his Durance.",bv="Kill Mephisto.",Av="Ask around the Docks about the Gidbinn.",xv="Ask Ormus about the Blackened Temple.",Nv="Ormus has news about the Guardian.",fv="Look for Izual in the Plains of Despair.",kv="Destroy the demon that holds Izual's soul.",Cv="Talk to Izual's Spirit.",yv="See Tyrael for reward.",Lv="Take Mephisto's Soulstone to the Hellforge.",Tv="Destroy Mephisto's Soulstone at the Hellforge.",Sv="Use the Hellforge Hammer on the Forge.",wv="Consult with Cain.",Dv="Find Diablo in his Sanctuary.",Pv="Kill Diablo.",Iv="Break the remaining %d seals.",Ev="Break the final seal.",Rv="Asheara",Bv="Hratli",qv="Alkor",Gv="Ormus",Uv="Natalya",Ov="Tyrael",zv="Izual",Fv="Izual",Wv="Jamella",jv="Halbu",_v="Hadriel",Vv="Hazade",Jv="Alhizeer",Qv="Azrael",Kv="Ahsab",Yv="Chalan",Xv="Haseen",$v="Razan",Zv="Emilio",eH="Pratham",aH="Fazel",rH="Jemali",iH="Kasim",nH="Gulzar",lH="Mizan",tH="Leharas",oH="Durga",sH="Neeraj",cH="Ilzan",mH="Zanarhi",pH="Waheed",dH="Vikhyat",uH="Jelani",gH="Barani",MH="Jabari",hH="Devak",vH="Raldin",HH="Telash",bH="Ajheed",AH="Narphet",xH="Khaleel",NH="Phaet",fH="Geshef",kH="Vanji",CH="Haphet",yH="Thadar",LH="Yatiraj",TH="Rhadge",SH="Yashied",wH="Jarulf",DH="Flux",PH="Scorch",IH="Khalim's Flail",EH="Khalim's Will",RH="Khalim's Flail",BH="Khalim's Will",qH="Khalim's Eye",GH="Khalim's Brain",UH="Khalim's Heart",OH="Impossible.",zH="I can't.",FH="Help Me!",WH="Help!",jH="Follow Me.",_H="Come on.",VH="This is for you.",JH="This is yours.",QH="Thank you.",KH="Thanks.",YH="Oops.",XH="Forgive me.",$H="Goodbye.",ZH="Bye.",eb="Die!",ab="Time to Die!",rb="Not enough mana.",ib="I need mana.",nb="I can't use this yet.",lb="I am overburdened.",tb="I can't carry anymore.",ob="Not in Town.",sb="Not Here.",cb="I can't do that here.",mb="It's Locked.",pb="I need a key.",db="I shall purge this land of the shadow.",ub="Beware foul demons and beasts.",gb="I will cleanse thiw widerness.",Mb="Evil beware!",hb="My enemies beware.",vb="I hear foul creatures about.",Hb="There are many foes here.",bb="Evil Dwells within this cave.",Ab="This place is trouble.",xb="I sense death within this place.",Nb="I sense great sorrow and misery.",fb="I shall meet death head-on.",kb="This holy place has been desecrated!",Cb="There is dark magic at work here.",yb="Too many empty graves.",Lb="So, this is the site of Andariel's atrocities.",Tb="The Monastery reeks with evil and corruption.",Sb="Even the Light cannot pierce this gloom.",wb="Ah, the Monastery... Andariel's stronghold!",Db="This place has the stench of demons about it.",Pb="What's that smell?",Ib="The stench of poison...",Eb="This tower shall be cleansed of evil.",Rb="This place holds many secrets.",Bb="This place reeks of death.",qb="What nightmarish tortures took place here?",Gb="No one should ever be caged.",Ub="This is no place for a warrior to die.",Ob="If there was magic here, it's long gone now.",zb="Ah, the slow torture of caged starvation.",Fb="Removed",Wb="This place is eerie.",jb="So cold and damp under the earth.",_b="There is great evil here.",Vb="This place chills me to the bone.",Jb="I sense a demonic presence here.",Qb="Perhaps now the Sisters will trust me.",Kb="The Rogues are safe for the moment.",Yb="My duty here is done.",Xb="This cave has been purged of evil.",$b="Is that enough to earn the Rogues' trust?",Zb="Rest in peace, Sister.",e6="Good riddance, Blood Raven.",a6="Sisters, there was no other way.",r6="Rest now, Blood Raven.",i6="Blood Raven... rest well.",n6="What a strange-looking tree...",l6="This tree is one of a kind.",t6="This tree bristles with magic!",o6="This ancient tree has an aura of magic about it.",s6="This tree shines with inner spirits.",c6="These stones serve some magical purpose...",m6="These magic stones are ancient.",p6="Maybe Akara could dispel the mystery of these stones.",d6="These stones radiate powerful magic.",u6="I sense many spirits around the stones.",g6="It's as if a great war were fought here.",M6="The land here is dead and lifeless.",h6="What a tragic end to Tristram!",v6="Tristram was no match for Diablo's fury.",H6="All that's left of proud Tristram are ghosts and ashes.",b6="Deckard Cain, go to the Rogues' camp without delay!",A6="Deckard Cain, you've got to get out of here!",x6="Deckard Cain, leave quickly!",N6="Deckard Cain, get to the Rogue camp!",f6="Deckard Cain, if you value your life, leave here immediately.",k6="The Sisters will be glad to have this back!",C6="I should take this to Charsi.",y6="This will help the Sisters turn the tide against evil.",L6="I hope the Sisters appreciate this thing...",T6="All this for a hammer?",S6="The Tower's trove... for the taking!",w6="This is reward enough!",D6="This tower has its charms...",P6="I hope to find other such treasures!",I6="Treasure hunting... bah... Treasure finding... yes.",E6="This Maiden shall inflict no more anguish.",R6="Let the gate be opened!",B6="My work here is finished.",q6="The evil queen has fallen.",G6="Back to the hell that spawned you, Andariel.",U6="This place disgusts me.",O6="Ugh... The tell-tale stench of a carnivore's lair.",z6="The foul stench of evil assails me.",F6="I sense strange magic here.",W6="I sense a powerful undead being within this place.",j6="Atma has been avenged.",_6="I've just about had my fill of the walking dead.",V6="I pray that Atma will rest easy now.",J6="What a misguided monster.",Q6="What a waste of undead flesh.",K6="Great. An eclipse. This just keeps getting better and better.",Y6="What is wrong with the sun?",X6="What Evil taints the light of the sun?",$6="Only powerful magic can conjure an eclipse.",Z6="Only the darkest magics can turn the sun black.",eA="I hope I know what I'm doing!",aA="The sun has never shone here!",rA="Light guide my way in this accursed place.",iA="I sense strong magic within this place.",nA="This place is as dark as a tomb.",lA="Let there be light.",tA="It is good to know that the sun shines once again.",oA="The Light can never be extinguished by evil.",sA="Who would have thought that such primitive beings could cause so much trouble!",cA="What a pity. I was beginning to enjoy the darkness.",mA="Am I the first to find this Arcane fortress?",pA="One could get lost in here.",dA="This surely is the product of a twisted mind!",uA="This place actually... distorts reality. Fascinating.",gA="This is fantastic! I wish I had time to study this bizarre dimension.",MA="What a freak!",hA="Stand aside, old fool. I have no time for your babblings.",vA="Surely the evil here has driven you mad.",HA="Is this truly Horazon?",bA="This bumbling fool cannot be the mighty Horazon!",AA="Good riddance, freak.",xA="I hate staining my hands with the blood of foul sorcerers.",NA="Rest in peace, tortured soul.",fA="That couldn't have been Horazon. Poor wretch.",kA="He was not Horazon. He was a deluded fool who got too close to true power!",CA="This has got to be the right place.",yA="This tomb is very ornate. This must be Tal Rasha's resting place.",LA="Is this the tomb I seek?",TA="This tomb has Horadric markings. I wonder if this is Tal Rasha's tomb?",SA="This could be Tal Rasha's tomb. However, I'm sensing very strange energies here.",wA="Should I enter...?  Diablo and Baal may have laid a trap...",DA="Such a cold breeze... Tal Rasha must be kept here.",PA="Here, at last, is a fitting testament in stone to Tal Rasha's sacrifice.",IA="This must be the true Tomb of Tal Rasha!",EA="I sense an incredible aura about this tomb. The Horadrim hid something powerful inside.",RA="This is not good. Will this madness ever end?",BA="I have failed. Diablo has freed his accursed brother. The world remains at their mercy.",qA="I shall honor Tal Rasha's sacrifice by destroying all the Prime Evils.",GA="Diablo and Baal have escaped me!  Next time... vengeance!",UA="I came too late. Now... Destruction is let loose upon the world once more.",OA="Not in Game",zA="I hope the secrets within this book can help us.",FA="I hope this book is worth all the trouble.",WA="The Black Book... It's heresy to the Zakarum High Council.",jA="This tome has the weight of knowledge about it.",_A="This ancient book radiates arcane power!",VA="All this trouble over a tattered book.",JA="May this book lift the shadow from Kurast.",QA="May the Black Book deliver us from evil!",KA="May the Black Book bring a black day to hell!",YA="Once the book has served its purpose, I shall delve into its secrets.",XA="Whoa.... What died down here?",$A="Cough... The stench down here is choking!",ZA="The smell of death... or worse... surrounds me.",ex="It smells worse than rotting reagents down here.",ax="It's been years since I waded through sewers for fun.",rx="I hope this does something good...",ix="This will drain out some of the filth.",nx="This appears to control the ancient valves.",lx="This looks promising.",tx="This looks like what I've been searching for.",ox="Eureka!",sx="Good. Now I can get out of here and get some fresh air!",cx="This trove will help lift the curse from Kurast!",mx="I hope these items can aid me against the demons.",px="Great. More junk. Just what I'd expect to find in a sewer...",dx="This dagger will separate the faithful from the fallen.",ux="This holy blade does not belong in the hands of the Zakarum.",gx="This blade shall pierce the heart of evil!",Mx="I must take this to Ormus.",hx="This is a powerful weapon. Perhaps Ormus can tell me more about it.",vx="A worthless statue. Perhaps I can trade this for something better.",Hx="Such a dark temple for a Religion of Light...",bx="The spirits of nature have fled this dreaded place.",Ax="This corrupted temple was once the shining heart of my religion...",xx="I sense tremendous evil within this place.",Nx="This temple exudes darkness.",fx="Skatsim's reign is renewed!",kx="The dark powers here will no longer poison the land.",Cx="The Temple shall shine anew with the Light.",yx="The Temple's power is annulled.",Lx="The Temple's dark power is broken.",Tx="This must be where Mephisto is.",Sx="The final resting place of Hatred itself.",wx="This must be where the Horadrim imprisoned Mephisto.",Dx="Ah... Mephisto's prison.",Px="The Tower that holds Mephisto....",Ix="Success... But still there's something not right.",Ex="Maybe now the world will have peace.",Rx="The Lord of Hatred shall darken the world no longer.",Bx="Mephisto shall no longer darken our souls with hatred.",qx="Good journey, Mephisto. Give my regards to the abyss.",Gx="Goodbye, Izual.",Ux="Even Fallen Angels deserve freedom.",Ox="How can one who was once so holy fall so far from righteousness?",zx="He was corrupted to the core. I pity him.",Fx="Bah! Izual was weak. He squandered his infernal power.",Wx="          ",jx="          ",_x="          ",Vx="          ",Jx="    ",Qx="           ",Kx="           ",Yx="    ",Xx="     ",$x="                       ",Zx="                       ",e7="     ",a7="           ",r7="           ",i7="                                                             ",n7="           ",l7="         ",t7="                   ",o7="                              ",s7="         ",c7="         ",m7="                           ",p7="                           ",d7="         ",u7="         ",g7="           ",M7="                                 ",h7="         ",v7="    ",H7="                     ",b7="                     ",A7="    ",x7="              ",N7="                       ",f7="                       ",k7="          ",C7="            ",y7="                   ",L7="                                     ",T7="            ",S7="           ",w7="                   ",D7="                   ",P7="           ",I7="                ",E7="                ",R7="                ",B7="         ",q7="    ",G7="                     ",U7="                     ",O7="    ",z7="        ",F7="                 ",W7="                                      ",j7="        ",_7="           ",V7="           ",J7="           ",Q7="           ",K7="          ",Y7="                           ",X7="                           ",$7="          ",Z7="         ",eN="         ",aN="                ",rN="         ",iN="     ",nN="     ",lN="     ",tN="     ",oN="    ",sN="    ",cN="    ",mN="    ",pN="       ",dN="                                ",uN="                                ",gN="       ",MN="            ",hN="                    ",vN="                    ",HN="            ",bN="       ",AN="                ",xN="                                               ",NN="       ",fN="   ",kN="                         ",CN="                         ",yN="   ",LN="       ",TN="                ",SN="                ",wN="       ",DN="       ",PN="                ",IN="                ",EN="       ",RN="               ",BN="                                ",qN="                                ",GN="               ",UN="              ",ON="              ",zN="              ",FN="              ",WN="           ",jN="                     ",_N="                                            ",VN="           ",JN="          ",QN="          ",KN="          ",YN="          ",XN="         ",$N="         ",ZN="         ",e8="         ",a8="           ",r8="                 ",i8="                 ",n8="           ",l8="     ",t8="     ",o8="                           ",s8="     ",c8="              ",m8="              ",p8="              ",d8="              ",u8="             ",g8="             ",M8="             ",h8="             ",v8="           ",H8="                  ",b8="                       ",A8="           ",x8="           ",N8="                      ",f8="                                      ",k8="           ",C8="             ",y8="                      ",L8="                      ",T8="             ",S8="          ",w8="                    ",D8="                                          ",P8="          ",I8="          ",E8="          ",R8="          ",B8="          ",q8="             ",G8="             ",U8="             ",O8="             ",z8="                   ",F8="                           ",W8="                                        ",j8="         ",_8="               ",V8="                       ",J8="                                       ",Q8="               ",K8="               ",Y8="               ",X8="               ",$8="               ",Z8="            ",ef="                            ",af="                                         ",rf="            ",nf="          ",lf="          ",tf="          ",of="          ",sf="          ",cf="          ",mf="          ",pf="          ",df="    ",uf="    ",gf="    ",Mf="    ",hf="            ",vf="            ",Hf="            ",bf="            ",Af="      ",xf="      ",Nf="      ",ff="      ",kf="                ",Cf="                ",yf="                ",Lf="                ",Tf="                ",Sf="                        ",wf="                                    ",Df="                ",Pf="          ",If="          ",Ef="          ",Rf="          ",Bf="          ",qf="          ",Gf="          ",Uf="          ",Of="          ",zf="          ",Ff="          ",Wf="          ",jf="             ",_f="             ",Vf="             ",Jf="             ",Qf="         ",Kf="         ",Yf="         ",Xf="         ",$f="            ",Zf="            ",ek="            ",ak="            ",rk="            ",ik="            ",nk="            ",lk="            ",tk="              ",ok="              ",sk="              ",ck="              ",mk="             ",pk="             ",dk="             ",uk="             ",gk="Ravens: ",Mk="Spikes: ",hk="Stars: ",vk="Wolf: ",Hk="Wolves: ",bk="Shoots ",Ak=" Times",xk=" Spikes",Nk="Eagle Orb",fk="Sacred Globe",kk="Smoked Sphere",Ck="Clasped Orb",yk="Jared's Stone",Lk="Preserved Head",Tk="Zombie Head",Sk="Unraveller Head",wk="Gargoyle Head",Dk="Demon Head",Pk="Wolf Head",Ik="Hawk Helm",Ek="Antlers",Rk="Falcon Mask",Bk="Spirit Mask",qk="Wraps",Gk="Knuckles",Uk="Slashers",Ok="Splay",zk="Hook",Fk="Shank",Wk="Claws",jk="(Amazon Only)",_k="(Sorceress Only)",Vk="(Necromancer Only)",Jk="(Paladin Only)",Qk="(Barbarian Only)",Kk="(Druid Only)",Yk="(Assassin Only)",Xk="Claw Class",$k="Rot Walker",Zk="Reanimated Horde",eC="Prowling Dead",aC="Unholy Corpse",rC="Defiled Warrior",iC="Crush Beast",nC="Blood Bringer",lC="Gore Bearer",tC="Demon Steed",oC="Wailing Spirit",sC="Life Seeker",cC="Life Stealer",mC="Deathly Visage",pC="Bound Spirit",dC="Banished Soul",uC="Death",gC="Enslaved",MC="Slayer",hC="Ice Boar",vC="Fire Boar",HC="Hell Spawn",bC="Ice Spawn",AC="Greater Hell Spawn",xC="Greater Ice Spawn",NC="Fanatic Enslaved",fC="Berserker Slayer",kC="Consumed Fire Boar",CC="Consumed Ice Boar",yC="Frenzied Hell Spawn",LC="Frenzied Ice Spawn",TC="Insane Hell Spawn",SC="Insane Ice Spawn",wC="Succubus",DC="Vile Temptress",PC="Stygian Harlot",IC="           ",EC="           ",RC="Siren",BC="Vile Witch",qC="Stygian Fury",GC="         ",UC="          ",OC="Overseer",zC="Lasher",FC="Overlord",WC="Blood Boss",jC="Hell Whip",_C="Demon Portal",VC="Demon Portal",JC="Demon Imp",QC="Demon Rascal",KC="Demon Gremlin",YC="Demon Trickster",XC="Demon Sprite",$C="     ",ZC="     ",ey="      ",ay="                ",ry="             ",iy="          ",ny="            ",ly="                 ",ty="                                                           ",oy="          ",sy="         ",cy="                            ",my="                                     ",py="            ",dy="          ",uy="                  ",gy="    ",My="   ",hy="              ",vy="              ",Hy="             ",by="           ",Ay="             ",xy="       ",Ny="    ",fy="     ",ky="   ",Cy="      ",yy="             ",Ly="   ",Ty="   ",Sy="   ",wy="   ",Dy="   ",Py="                              ",Iy="                             ",Ey="                                 ",Ry="                                ",By="                            ",qy="                      ",Gy="                        ",Uy="                                                                  ",Oy="                               ",zy="                     ",Fy="                                      ",Wy="                     ",jy="                      ",_y="                                 ",Vy="      ",Jy="              ",Qy="     ",Ky="             ",Yy="           ",Xy="                 ",$y="               ",Zy="                                                 ",eL="                     ",aL="                            ",rL="                    ",iL="                  ",nL="    ",lL="%0 %1",tL="%0 %1",oL="%0 %1",sL="%0 %1",cL="%0 %1",mL="%0 %1 %2",pL="%0 %1",dL="%0 %1",uL="%0 %1",gL="%0 %1",ML="%0 %1",hL="%0 %1",vL="%0 %1",HL="%0 %1 %2",bL="Damaged",AL="Cracked",xL="Crude",NL="Superior",fL="Gemmed",kL="Resilient",CL="Sturdy",yL="Strong",LL="Glorious",TL="Blessed",SL="Saintly",wL="Holy",DL="Devious",PL="Fortified",IL="Urgent",EL="Fleet",RL="Muscular",BL="Jagged",qL="Deadly",GL="Vicious",UL="Brutal",OL="Massive",zL="Savage",FL="Merciless",WL="Vulpine",jL="Swift",_L="Artful",VL="Skillful",JL="Adroit",QL="Tireless",KL="Rugged",YL="Bronze",XL="Iron",$L="Steel",ZL="Silver",eT="Gold",aT="Platinum",rT="Meteoric",iT="Sharp",nT="Fine",lT="Howling",tT="Fortuitous",oT="Brilliant",sT="Omniscient",cT="Sage",mT="Shrewd",pT="Vivid",dT="Glimmering",uT="Glowing",gT="Bright",MT="Solar",hT="Forceful",vT="Dazzling",HT="Fascinating",bT="Prismatic",AT="Azure",xT="Lapis",NT="Cobalt",fT="Indigo",kT="Sapphire",CT="Cerulean",yT="Red",LT="Crimson",TT="Burgundy",ST="Garnet",wT="Russet",DT="Ruby",PT="Vermilion",IT="Orange",ET="Ocher",RT="Tangerine",BT="Coral",qT="Crackling",GT="Amber",UT="Forked",OT="Green",zT="Beryl",FT="Jade",WT="Viridian",jT="Vital",_T="Emerald",VT="Enduring",JT="Kicking",QT="Triumphant",KT="Mighty",YT="Energizing",XT="Strengthening",$T="Empowering",ZT="Brisk",e9="Tough",a9="Hardy",r9="Robust",i9="Cap",n9="Skull Cap",l9="Helm",t9="Full Helm",o9="Great Helm",s9="Crown",c9="Mask",m9="Quilted Armor",p9="Leather Armor",d9="Hard Leather Armor",u9="Studded Leather",g9="Ring Mail",M9="Scale Mail",h9="Chain Mail",v9="Breast Plate",H9="Splint Mail",b9="Plate Mail",A9="Field Plate",x9="Gothic Plate",N9="Full Plate Mail",f9="Ancient Armor",k9="Light Plate",C9="Buckler",y9="Small Shield",L9="Large Shield",T9="Kite Shield",S9="Tower Shield",w9="Gothic Shield",D9="Leather Gloves",P9="Heavy Gloves",I9="Chain Gloves",E9="Light Gauntlets",R9="Gauntlets",B9="Boots",q9="Heavy Boots",G9="Chain Boots",U9="Light Plated Boots",O9="Greaves",z9="Sash",F9="Light Belt",W9="Belt",j9="Heavy Belt",_9="Plated Belt",V9="Bone Helm",J9="Bone Shield",Q9="Spiked Shield",K9="Hand Axe",Y9="Axe",X9="Military Pick",$9="War Axe",Z9="Large Axe",eS="Broad Axe",aS="Battle Axe",rS="Great Axe",iS="Giant Axe",nS="Wand",lS="Yew Wand",tS="Bone Wand",oS="Grim Wand",sS="Club",cS="Scepter",mS="Grand Scepter",pS="War Scepter",dS="Spiked Club",uS="Mace",gS="Morning Star",MS="Flail",hS="War Hammer",vS="Maul",HS="Great Maul",bS="Short Sword",AS="Scimitar",xS="Sabre",NS="Falchion",fS="Crystal Sword",kS="Broad Sword",CS="Long Sword",yS="War Sword",LS="Claymore",TS="Giant Sword",SS="Bastard Sword",wS="Flamberge",DS="Great Sword",PS="Dagger",IS="Dirk",ES="Kris",RS="Blade",BS="Throwing Knife",qS="Throwing Axe",GS="Balanced Knife",US="Balanced Axe",OS="Javelin",zS="Pilum",FS="Short Spear",WS="Glaive",jS="Throwing Spear",_S="Spear",VS="Trident",JS="Brandistock",QS="Spetum",KS="Pike",YS="Bardiche",XS="Voulge",$S="Scythe",ZS="Poleaxe",ew="Halberd",aw="War Scythe",rw="Short Staff",iw="Long Staff",nw="Gnarled Staff",lw="Battle Staff",tw="War Staff",ow="Short Bow",sw="Hunter's Bow",cw="Long Bow",mw="Composite Bow",pw="Short Battle Bow",dw="Long Battle Bow",uw="Short War Bow",gw="Long War Bow",Mw="Light Crossbow",hw="Crossbow",vw="Heavy Crossbow",Hw="Repeating Crossbow",bw="Barbed Shield",Aw="Grim Shield",xw="Grim Helm",Nw="War Belt",fw="Battle Belt",kw="Mesh Belt",Cw="Sharkskin Belt",yw="Demonhide Sash",Lw="War Boots",Tw="Battle Boots",Sw="Mesh Boots",ww="Sharkskin Boots",Dw="Demonhide Boots",Pw="War Gauntlets",Iw="Battle Gauntlets",Ew="Heavy Bracers",Rw="Sharkskin Gloves",Bw="Demonhide Gloves",qw="Ancient Shield",Gw="Pavise",Uw="Dragon Shield",Ow="Scutum",zw="Round Shield",Fw="Defender",Ww="Mage Plate",jw="Ornate Plate",_w="Chaos Armor",Vw="Embossed Plate",Jw="Sharktooth Armor",Qw="Templar Coat",Kw="Russet Armor",Yw="Cuirass",Xw="Mesh Armor",$w="Tigulated Mail",Zw="Linked Mail",eD="Trellised Armor",aD="Demonhide Armor",rD="Serpentskin Armor",iD="Ghost Armor",nD="Death Mask",lD="Grand Crown",tD="Winged Helm",oD="Basinet",sD="Casque",cD="Sallet",mD="War Hat",pD="Strangling Gas Potion",dD="Fulminating Potion",uD="Choking Gas Potion",gD="Exploding Potion",MD="Rancid Gas Potion",hD="Oil Potion",vD="Gidbinn",HD="The Gidbinn",bD="Decoy Gidbinn",AD="Wirt's Leg",xD="Horadric Malus",ND="Horadric Malus",fD="Hell Forge Hammer",kD="Horadric Staff",CD="Shaft of the Horadric Staff",yD="orifice",LD="Elixir",TD="Tome of Town Portal",SD="Scroll of Town Portal",wD="Tome of Identify",DD="Scroll of Identify",PD="Right Click to Use",ID="Right Click to Open",ED="Right Click to Read",RD="Insert Scrolls",BD="Stamina Potion",qD="Antidote Potion",GD="Rejuvenation Potion",UD="Full Rejuvenation Potion",OD="Thawing Potion",zD="Amulet",FD="Top of the Horadric Staff",WD="Ring",jD="Gold",_D="Scroll of Inifuss",VD="Key to the Cairn Stones",JD="Arrows",QD="Torch",KD="Bolts",YD="Key",XD="Key",$D="The Black Tower Key",ZD=`Right Click to permanently add 20 to Life
Potion of Life`,eP="shrine",aP="A Jade Figurine",rP="The Golden Bird",iP="Lam Esen's Tome",nP="Lam Esen's Tome",lP="Horadric Cube",tP="Horadric Scroll",oP="Mephisto's Soulstone",sP=`Right Click to learn skill of your choice
Book of Skill`,cP="Ear",mP="Chipped Amethyst",pP="Flawed Amethyst",dP="Amethyst",uP="Flawless Amethyst",gP="Perfect Amethyst",MP="Chipped Topaz",hP="Flawed Topaz",vP="Topaz",HP="Flawless Topaz",bP="Perfect Topaz",AP="Chipped Sapphire",xP="Flawed Sapphire",NP="Sapphire",fP="Flawless Sapphire",kP="Perfect Sapphire",CP="Chipped Emerald",yP="Flawed Emerald",LP="Flawless Emerald",TP="Emerald",SP="Perfect Emerald",wP="Chipped Ruby",DP="Flawed Ruby",PP="Ruby",IP="Flawless Ruby",EP="Perfect Ruby",RP="Chipped Diamond",BP="Flawed Diamond",qP="Diamond",GP="Flawless Diamond",UP="Perfect Diamond",OP="Minor Healing Potion",zP="Light Healing Potion",FP="Healing Potion",WP="Greater Healing Potion",jP="Super Healing Potion",_P="Minor Mana Potion",VP="Light Mana Potion",JP="Mana Potion",QP="Greater Mana Potion",KP="Super Mana Potion",YP="Herb",XP="Chipped Skull",$P="Flawed Skull",ZP="Skull",eI="Flawless Skull",aI="Perfect Skull",rI="Beast",iI="Eagle",nI="Raven",lI="Viper",tI="Ghoul",oI="Skull",sI="Blood",cI="Dread",mI="Doom",pI="Grim",dI="Bone",uI="Death",gI="Shadow",MI="Storm",hI="Rune",vI="Plague",HI="Stone",bI="Wraith",AI="Spirit",xI="Demon",NI="Cruel",fI="Empyrian",kI="Bramble",CI="Pain",yI="Loath",LI="Glyph",TI="Imp",SI="Fiend",wI="Hailstone",DI="Gale",PI="Dire",II="Soul",EI="Brimstone",RI="Corpse",BI="Carrion",qI="Armageddon",GI="Havoc",UI="Bitter",OI="Entropy",zI="Chaos",FI="Order",WI="Rift",jI="Corruption",_I="Bite",VI="Scratch",JI="Scalpel",QI="Fang",KI="Gutter",YI="Thirst",XI="Razor",$I="Scythe",ZI="Edge",eE="Saw",aE="Splitter",rE="Cleaver",iE="Sever",nE="Sunder",lE="Rend",tE="Mangler",oE="Slayer",sE="Reaver",cE="Spawn",mE="Gnash",pE="Star",dE="Blow",uE="Smasher",gE="Bane",ME="Crusher",hE="Breaker",vE="Grinder",HE="Crack",bE="Mallet",AE="Knell",xE="Lance",NE="Spike",fE="Impaler",kE="Skewer",CE="Prod",yE="Scourge",LE="Wand",TE="Wrack",SE="Barb",wE="Needle",DE="Dart",PE="Bolt",IE="Quarrel",EE="Fletch",RE="Flight",BE="Nock",qE="Horn",GE="Stinger",UE="Quill",OE="Goad",zE="Branch",FE="Spire",WE="Song",jE="Call",_E="Cry",VE="Spell",JE="Chant",QE="Weaver",KE="Gnarl",YE="Visage",XE="Crest",$E="Circlet",ZE="Veil",eR="Hood",aR="Mask",rR="Brow",iR="Casque",nR="Visor",lR="Cowl",tR="Hide",oR="Pelt",sR="Carapace",cR="Coat",mR="Wrap",pR="Suit",dR="Cloak",uR="Shroud",gR="Jack",MR="Mantle",hR="Guard",vR="Badge",HR="Rock",bR="Aegis",AR="Ward",xR="Tower",NR="Shield",fR="Wing",kR="Mark",CR="Emblem",yR="Hand",LR="Fist",TR="Claw",SR="Clutches",wR="Grip",DR="Grasp",PR="Hold",IR="Touch",ER="Finger",RR="Knuckle",BR="Shank",qR="Spur",GR="Tread",UR="Stalker",OR="Greaves",zR="Blazer",FR="Nails",WR="Trample",jR="Brogues",_R="Track",VR="Slippers",JR="Clasp",QR="Buckle",KR="Harness",YR="Lock",XR="Fringe",$R="Winding",ZR="Chain",eB="Strap",aB="Lash",rB="Cord",iB="Knot",nB="Circle",lB="Loop",tB="Eye",oB="Turn",sB="Spiral",cB="Coil",mB="Gyre",pB="Band",dB="Whorl",uB="Talisman",gB="Heart",MB="Noose",hB="Necklace",vB="Collar",HB="Beads",bB="Torc",AB="Gorget",xB="Scarab",NB="Wood",fB="Brand",kB="Bludgeon",CB="Cudgel",yB="Loom",LB="Harp",TB="Master",SB="Bar",wB="Hew",DB="Crook",PB="Mar",IB="Shell",EB="Stake",RB="Picket",BB="Pale",qB="Flange",GB="Infernal",UB="Angelic",OB="Arctic",zB="Ward",FB="Tooth",WB="Collar",jB="Lightbrand",_B="Barb",VB="Orb",JB="Rule",QB="Crowbill",KB="Visor",YB="Cranium",XB="Headgear",$B="Hand",ZB="Sickle",eq="Horn",aq="Sign",rq="Icon",iq="Claw",nq="Cuff",lq="Parry",tq="Fetlock",oq="Rod",sq="Mesh",cq="Spine",mq="Shelter",pq="Torch",dq="Hauberk",uq="Guard",gq="Mantle",Mq="Furs",hq="Deathwand",vq="Cudgel",Hq="Pincers",bq="Coil",Aq="Case",xq="Ambush",Nq="Diadem",fq="Visage",kq="Hobnails",Cq="Gage",yq="Buckle",Lq="Hatchet",Tq="Touch",Sq="Halo",wq="Binding",Dq="Head",Pq="Horns",Iq="Snare",Eq="Robe",Rq="Sigil",Bq="Weird",qq="Sabot",Gq="Wings",Uq="Mitts",Oq="Flesh",zq="Cord",Fq="Seal",Wq="Skull",jq="Wrap",_q="Guard",Vq="Deathspade",Jq="Bladebone",Qq="Skull Splitter",Kq="Rakescar",Yq="Goreshovel",Xq="Brainhew",$q="Maelstrom",Zq="Gravenspine",eG="Felloak",aG="Rusthandle",rG="Stormeye",iG="Stoutnail",nG="Crushflange",lG="Bloodrise",tG="Ironstone",oG="Bonesnap",sG="Steeldriver",cG="Gleamscythe",mG="Azurewrath",pG="Hellplague",dG="Shadowfang",uG="Soulflay",gG="Blacktongue",MG="Ripsaw",hG="Gull",vG="Razortine",HG="Bloodthief",bG="Steelgoad",AG="Woestave",xG="Pluckeye",NG="Witherstring",fG="Raven Claw",kG="Rogue's Bow",CG="Stormstrike",yG="Wizendraw",LG="Hellclap",TG="Blastbark",SG="Leadcrow",wG="Ichorsting",DG="Hellcast",PG="Doomslinger",IG="Tarnhelm",EG="Duskdeep",RG="Wormskull",BG="Howltusk",qG="Greyform",GG="Twitchthroe",UG="Darkglow",OG="Hawkmail",zG="Venom Ward",FG="Iceblink",WG="Boneflesh",jG="Rockfleece",_G="Rattlecage",VG="Goldskin",JG="Stormguild",QG="Steelclash",KG="Bloodfist",YG="Magefist",XG="Frostburn",$G="Hotspur",ZG="Gorefoot",eU="Tearhaunch",aU="Snakecord",rU="Nightsmoke",iU="Goldwrap",nU="Bladebuckle",lU="Nagelring",tU="Gorgethroat",oU="Gloom",sU="Gray",cU="Dire",mU="Black",pU="Shadow",dU="Haze",uU="Wind",gU="Storm",MU="Warp",hU="Night",vU="Moon",HU="Star",bU="Pit",AU="Flame",xU="Ice",NU="Seethe",fU="Sharp",kU="Ash",CU="Blade",yU="Steel",LU="Stone",TU="Rust",SU="Mold",wU="Blight",DU="Plague",PU="Rot",IU="Ooze",EU="Puke",RU="Snot",BU="Bile",qU="Blood",GU="Pulse",UU="Gut",OU="Gore",zU="Flesh",FU="Bone",WU="Spine",jU="Mind",_U="Spirit",VU="Soul",JU="Wrath",QU="Grief",KU="Foul",YU="Vile",XU="Sin",$U="Chaos",ZU="Dread",eO="Doom",aO="Bane",rO="Death",iO="Viper",nO="Dragon",lO="Devil",tO="Touch",oO="Spell",sO="Feast",cO="Wound",mO="Grin",pO="Maim",dO="Hack",uO="Bite",gO="Rend",MO="Burn",hO="Ripper",vO="Kill",HO="Call",bO="Vex",AO="Jade",xO="Web",NO="Shield",fO="Killer",kO="Razor",CO="Drinker",yO="Shifter",LO="Crawler",TO="Dancer",SO="Bender",wO="Weaver",DO="Eater",PO="Widow",IO="Maggot",EO="Spawn",RO="Wight",BO="Grumble",qO="Growler",GO="Snarl",UO="Wolf",OO="Crow",zO="Raven",FO="Hawk",WO="Cloud",jO="Bang",_O="Head",VO="Skull",JO="Brow",QO="Eye",KO="Maw",YO="Tongue",XO="Fang",$O="Horn",ZO="Thorn",ez="Claw",az="Fist",rz="Heart",iz="Shank",nz="Skin",lz="Wing",tz="Pox",oz="Fester",sz="Blister",cz="Pus",mz="Slime",pz="Drool",dz="Froth",uz="Sludge",gz="Venom",Mz="Poison",hz="Shard",vz="Flame",Hz="Maul",bz="Thirst",Az="Lust",xz="the Quick",Nz="Taintbreeder",fz="Stormtree",kz="Bishibosh",Cz="Bonebreaker",yz="Coldcrow",Lz="Rakanishu",Tz="Griswold",Sz="Bone Ash",wz="Radament",Dz="Fangskin",Pz="Beetleburst",Iz="Creeping Feature",Ez="Deckard Cain",Rz="Gheed",Bz="Akara",qz="Kashya",Gz="Charsi",Uz="Warriv",Oz="Warriv",zz="Rogue",Fz="Stygian Doll",Wz="Soul Killer",jz="Flayer",_z="Fetish",Vz="Rat Man",Jz="Dark Familiar",Qz="Blood Diver",Kz="Gloombat",Yz="Desert Wing",Xz="The Banished",$z="Blood Lord",Zz="Dark Lord",eF="Night Lord",aF="Ghoul Lord",rF="Spikefist",iF="Thrasher",nF="Bramble Hulk",lF="Thorned Hulk",tF="Spider Magus",oF="Flame Spider",sF="Poison Spinner",cF="Sand Fisher",mF="Arach",pF="Blood Wing",dF="Blood Hook",uF="Feeder",gF="Sucker",MF="Winged Nightmare",hF="Hell Buzzard",vF="Undead Scavenger",HF="Carrion Bird",bF="Unraveler",AF="Guardian",xF="Hollow One",NF="Bone Scarab",fF="Steel Scarab",kF="Scarab",CF="Death Beetle",yF="Dung Soldier",LF="Hell Swarm",TF="Plague Bugs",SF="Black Locusts",wF="Itchies",DF="Hell Cat",PF="Night Tiger",IF="Saber Cat",EF="Huntress",RF="Cliff Lurker",BF="Tree Lurker",qF="Cave Leaper",GF="Tomb Creeper",UF="Sand Leaper",OF="Tomb Viper",zF="Pit Viper",FF="Salamander",WF="Claw Viper",jF="Serpent Magus",_F="Blood Maggot",VF="Giant Lamprey",JF="Devourer",QF="Rock Worm",KF="Sand Maggot",YF="Bush Barb",XF="Razor Spine",$F="Thorn Beast",ZF="Spike Fiend",eW="Quill Rat",aW="Hell Clan",rW="Moon Clan",iW="Night Clan",nW="Death Clan",lW="Blood Clan",tW="Temple Guard",oW="Doom Ape",sW="Jungle Hunter",cW="Rock Dweller",mW="Dune Beast",pW="Flesh Hunter",dW="Black Rogue",uW="Dark Stalker",gW="Vile Hunter",MW="Dark Hunter",hW="Dark Shape",vW="Apparition",HW="Specter",bW="Ghost",AW="Assailant",xW="Infidel",NW="Invader",fW="Marauder",kW="Sand Raider",CW="Gargantuan Beast",yW="Wailing Beast",LW="Yeti",TW="Crusher",SW="Brute",wW="Cloud Stalker",DW="Black Vulture",PW="Black Raptor",IW="Blood Hawk",EW="Foul Crow",RW="Plague Bearer",BW="Ghoul",qW="Drowned Carcass",GW="Hungry Dead",UW="Zombie",OW="Skeleton",zW="Horror",FW="Returned",WW="Burning Dead",jW="Bone Warrior",_W="Damned",VW="Disfigured",JW="Misshapen",QW="Tainted",KW="Afflicted",YW="Andariel",XW="Natalya",$W="Drognan",ZW="Atma",ej="Fara",aj="Lysander",rj="Jerhyn",ij="Jerhyn",nj="Geglash",lj="Elzix",tj="Greiz",oj="Meshif",sj="Camel",cj="Cadaver",mj="Preserved Dead",pj="Embalmed",dj="Dried Corpse",uj="Decayed",gj="Urdar",Mj="Mauler",hj="Gorebelly",vj="Blunderbore",Hj="Blood Maggot Young",bj="Giant Lamprey Young",Aj="Devourer Young",xj="Rock Worm Young",Nj="Sand Maggot Young",fj="Blood Maggot Egg",kj="Giant Lamprey Egg",Cj="Devourer Egg",yj="Rock Worm Egg",Lj="Sand Maggot Egg",Tj="Maggot",Sj="Duriel",wj="Blood Hawk Nest",Dj="Flying Scimitar",Pj="Cloud Stalker Nest",Ij="Black Raptor Nest",Ej="Foul Crow Nest",Rj="Diablo",Bj="Baal",qj="Mephisto",Gj="Cantor",Uj="Heirophant",Oj="Sexton",zj="Zealot",Fj="Faithful",Wj="Zakarumite",jj="Black Soul",_j="Burning Soul",Vj="Swamp Ghost",Jj="Gloam",Qj="Warped Shaman",Kj="Dark Shaman",Yj="Devilkin Shaman",Xj="Carver Shaman",$j="Fallen Shaman",Zj="Warped One",e_="Dark One",a_="Devilkin",r_="Carver",i_="Fallen",n_="Returned Archer",l_="Horror Archer",t_="Burning Dead Archer",o_="Bone Archer",s_="Corpse Archer",c_="Skeleton Archer",m_="Flesh Lancer",p_="Black Lancer",d_="Dark Lancer",u_="Vile Lancer",g_="Dark Spearwoman",M_="Flesh Archer",h_="Black Archer",v_="Dark Ranger",H_="Vile Archer",b_="Dark Archer",A_="The Summoner",x_="Stygian Doll Shaman",N_="Soul Killer Shaman",f_="Flayer Shaman",k_="Fetish Shaman",C_="RatMan Shaman",y_="Horror Mage",L_="Burning Dead Mage",T_="Bone Mage",S_="Corpse Mage",w_="Returned Mage",D_="Gargoyle Trap",P_="Blood Raven",I_="Flavie",E_="Kaelan",R_="Meshif",B_="Stygian Watcher",q_="River Stalker",G_="Water Watcher",U_="Stygian Watcher",O_="River Stalker",z_="Water Watcher",F_="Night Marauder",W_="Fire Golem",j_="Iron Golem",__="Blood Golem",V_="Clay Golem",J_="Blood Maggot Queen",Q_="Giant Lamprey Queen",K_="Devourer Queen",Y_="Rock Worm Queen",X_="Sand Maggot Queen",$_="Barbed Giant",Z_="Razor Beast",eV="Thorn Brute",aV="Spike Giant",rV="Quill Bear",iV="Dark Wanderer",nV="Dark Wanderer",lV="Hell Slinger",tV="Night Slinger",oV="Spear Cat",sV="Slinger",cV="Fire Tower",mV="Lightning Spire",pV="Pit Lord",dV="Balrog",uV="Venom Lord",gV="Inviso Spawner",MV="Oblivion Knight",hV="Mage",vV="Abyss Knight",HV="Doom Knight",bV="Fighter",AV="Maw Fiend",xV="Corpse Spitter",NV="Corpulent",fV="Storm Caster",kV="Strangler",CV="Doom Caster",yV="Grotesque Wyrm",LV="Stygian Dog",TV="Flesh Beast",SV="Grotesque",wV="Stygian Hag",DV="Flesh Spawner",PV="Rogue Scout",IV="Blood Wing Nest",EV="Blood Hook Nest",RV="Feeder Nest",BV="Sucker Nest",qV="Necromage",GV="Necroskeleton",UV="Trapped Soul",OV="Valkyrie",zV="Decoy",FV="Extra Strong",WV="Extra Fast",jV="Cursed",_V="Magic Resistant",VV="Fire Enchanted",JV="Cold Enchanted",QV="Lightning Enchanted",KV="Mana Burn",YV="Spectral Hit",XV="Teleportation",$V="Stone Skin",ZV="Multiple Shots",eJ="Thief",aJ="Aura Enchanted",rJ="Champion",iJ="Minion",nJ="Barrel",lJ="Lever",tJ="an Exploding Barrel",oJ="Closed Door",sJ="Portal to ",cJ="Open Door",mJ="Blocked Door",pJ="Locked Door",dJ="Cairn Stone",uJ="Cairn Stone",gJ="Cairn Stone",MJ="Cairn Stone",hJ="Cairn Stone",vJ="Cairn Stone",HJ="Crate",bJ="Casket",AJ="Cabinet",xJ="Vase",NJ="Tree of Inifuss",fJ="Corpse",kJ="Dead Rogue",CJ="Dead Rogue",yJ="The Moldy Tome",LJ="Cain's Gibbet",TJ="Mummy Sarcophagus",SJ="Armor Stand",wJ="Weapon Rack",DJ="Sarcophagus",PJ="Large Urn",IJ="Canopic Jar",EJ="Obelisk",RJ="Undefiled Grave",BJ="Shrine",qJ="Urn",GJ="Waypoint",UJ="Well",OJ="Bag",zJ="Chest",FJ="Chest",WJ="Locked Chest",jJ="Horazon's Journal",_J="shrine",VJ="Stair",JJ="Coffin",QJ="Bookshelf",KJ="Fire",YJ="Chest",XJ="Guard Corpse",$J="Bowl",ZJ="Jug",eQ="Ambient Sound",aQ="Rat's Nest",rQ="Well",iQ="Door",nQ="Skeleton",lQ="Skullpile",tQ="Cocoon",oQ="Cow",sQ="Shrine",cQ="Bed",mQ="Chest",pQ="Your Private Stash",dQ="Holyshrine",uQ="Body",gQ="Compelling Orb",MQ="Basket",hQ="Basket",vQ="Rock Pile",HQ="Horazon's Journal",bQ="Eunuch",AQ="Portal",xQ="Sarcophagus",NQ="Stash",fQ="Suffering Soul",kQ="Tainted Sun Altar",CQ="Hellforge",yQ="Corpsefire",LQ="fissure",TQ="Bone Chest",SQ="Casket",wQ="Hung Skeleton",DQ="Pillar",PQ="Hydra",IQ="a Turret",EQ="Cost: ",RQ="Repair cost: ",BQ="Sell value: ",qQ="Identify cost: ",GQ="Item cannot be traded here.",UQ="trade/repair",OQ="Buy",zQ="Sell",FQ="Heal :",WQ="Repair",jQ="Next Page",_Q="Previous Page",VQ="Accept Trade",JQ="     Your Gold: ",QQ="Which item should be imbued?",KQ="Yes",YQ="No",XQ="Gold:",$Q="Sell",ZQ="Buy",eK="Hire",aK="Identify",rK="Repair",iK="This Mercenary will replace your current one.",nK="Waiting for confirmation of transaction...",lK="Sync error on transaction, please try again.",tK="Invalid item detected, player will be dropped.",oK="You do not have enough free space to do that.",sK="You already have the maximum number of Mercenaries.",cK="That item has just been traded.",mK="You do not have enough room for the gold.",pK="Something tells me that you do not have that item.",dK="I cannot complete that request.",uK="You do not have enough gold for that.",gK="She cannot come right now.  Try again later.",MK="Your Gold: %d     Hire which Mercenary?",hK="There are no Mercenaries left to hire.",vK="Life",HK="Def",bK="Lvl",AK="Cost",xK="Damage",NK="Fire Arrow",fK="Cold Arrow",kK="Jab Attack",CK="Poison Resistant",yK="Lightning",LK="Cold",TK="Fire",SK="Lightning, Fast Cast",wK="Cold, Fast Cast",DK="Fire, Fast Cast",PK="talk",IK="go east",EK="go west",RK="sail east",BK="sail west",qK="important news",GK="urgent news",UK="pressing matters",OK="important news",zK="urgent matters",FK="tell me more",WK="about the merchants",jK="the townspeople",_K="leave",VK="gossip",JK="trade",QK="hire",KK="gamble",YK="introduction",XK="cancel",$K="ok",ZK="CANCEL",eY="Continue",aY="_",rY="Music",iY="Sound",nY="Gamma",lY="Render",tY="Previous Menu",oY="Configure Controls",sY="Aliza",cY="Amplisa",mY="Annor",pY="Abhaya",dY="Elly",uY="Paige",gY="Basanti",MY="Blaise",hY="Kyoko",vY="Klaudia",HY="Kundri",bY="Kyle",AY="Visala",xY="Elexa",NY="Floria",fY="Fiona",kY="Gwinni",CY="Gaile",yY="Hannah",LY="Heather",TY="Iantha",SY="Diane",wY="Isolde",DY="Divo",PY="Ithera",IY="Itonya",EY="Liene",RY="Maeko",BY="Mahala",qY="Liaza",GY="Meghan",UY="Olena",OY="Oriana",zY="Ryann",FY="Rozene",WY="Raissa",jY="Sharyn",_Y="Shikha",VY="Debi",JY="Tylena",QY="Wendy",KY="I feel much stronger now",YY="Socketed",XY="Requirements not met",$Y="Unidentified",ZY="Charges:",eX="Durability:",aX="Required Strength:",rX="Required Dexterity:",iX="Damage:",nX="Defense:",lX="Quantity:",tX="of",oX="to",sX="One-Hand Damage:",cX="Two-Hand Damage:",mX="Throw Damage:",pX="Smite Damage:",dX="Required Level:",uX="Points:",gX="Heals 35% Life and Mana",MX="Heals 100% Life and Mana",hX="to Strength",vX="to Dexterity",HX="to Vitality",bX="to Energy",AX="to Mana",xX="to Maximum Damage",NX="to Minimum Damage",fX="to Attack Rating",kX="Defense",CX="Fire Resist",yX="Cold Resist",LX="Lightning Resist",TX="Magic Resist",SX="Poison Resist",wX="to Maximum Fire Damage",DX="to Minimum Fire Damage",PX="to Maximum Lightning Damage",IX="to Minimum Lightning Damage",EX="to Maximum Cold Damage",RX="to Minimum Cold Damage",BX="to Life",qX="Attacker Takes Damage of",GX="Extra Gold from Monsters",UX="Better Chance of Getting Magic Items",OX="Knockback",zX="Elixir of Strength",FX="Elixir of Dexterity",WX="Elixir of Energy",jX="Elixir of Vitality",_X="Elixir of Mana",VX="Elixir of Life",JX="Sec. Duration",QX="Increase Maximum Life",KX="Increase Maximum Mana",YX="Increase Maximum Durability",XX="Enhanced Maximum Damage",$X="Enhanced Minimum Damage",ZX="Replenish Life",e$="Replenish Mana",a$="Heal 1/4 Life",r$="Heal 1/2 Life",i$="Restore Full Life",n$="Replenish 1/4 Mana",l$="Replenish 1/2 Life",t$="Restore Full Mana",o$="Magic Damage Reduced by",s$="Damage Reduced by",c$="Enhanced Defense",m$="Drain Life",p$="Drain Mana",d$="Mana stolen per hit",u$="Life stolen per hit",g$="to Amazon Skill Levels",M$="to Paladin Skill Levels",h$="to Necromancer Skill Levels",v$="to Sorceress Skill Levels",H$="to Barbarian Skill Levels",b$="to Light Radius",A$="Increased Chance of Blocking",x$="Requirements",N$="to Fire Skills",f$="Attacker Takes Lightning Damage of",k$="to All Skills",C$="Freezes target",y$="Chance of Open Wounds",L$="Invisibility",T$="Neutral Invisibility",S$="No Mana Healing",w$="No Life Healing",D$="Poison Length Reduced by",P$="Hit Causes Monster to Flee",I$="Heal Stamina Plus",E$="Damage Taken Goes To Mana",R$="Heal Life Plus",B$="Ignore Target's Defense",q$="Half Poison Duration",G$="Prevent Monster Heal",U$="Half Freeze Duration",O$="Bonus to Attack Rating",z$="to Monster Defense Per Hit",F$="Damage to Demons",W$="Damage to Undead",j$="Regenerate Mana",_$="to Maximum Poison Damage",V$="to Minimum Poison Damage",J$="to Attack Rating against Demons",Q$="to Attack Rating against Undead",K$="Slightly Increased Attack Speed",Y$="Increased Attack Speed",X$="Greatly Increased Attack Speed",$$="Fast Hit Recovery",Z$="Faster Hit Recovery",eZ="Fastest Hit Recovery",aZ="Fast Run/Walk",rZ="Faster Run/Walk",iZ="Fastest Run/Walk",nZ="Fast Cast Rate",lZ="Faster Cast Rate",tZ="Fastest Cast Rate",oZ="Fast Block Rate",sZ="Faster Block Rate",cZ="Fastest Block Rate",mZ="Throwable",pZ="Damage",dZ="Chance of Crushing Blow",uZ="Maximum Stamina",gZ="Kick Damage",MZ="to Mana after each Kill",hZ="Fire Absorb",vZ="Fire Absorb",HZ="Lightning Absorb",bZ="Lightning Absorb",AZ="Magic Absorb",xZ="Magic Absorb",NZ="Cold Absorb",fZ="Cold Absorb",kZ="Target Defense",CZ="Extra Bloody",yZ="Deadly Strike",LZ="Slows Target by",TZ="Blessed Aim",SZ="Defiance",wZ="to Maximum Fire Resist",DZ="to Maximum Cold Resist",PZ="to Maximum Lightning Resist",IZ="to Maximum Magic Resist",EZ="to Maximum Poison Resist",RZ="Cannot Be Frozen",BZ="Defense vs. Missile",qZ="Defense vs. Melee",GZ="Life after each Demon Kill",UZ="Hit Blinds Target",OZ="Slower Stamina Drain",zZ="Chance to Reanimate Target",FZ="Piercing Attack",WZ="Fires Magic Arrows",jZ="Fires Explosive Arrows or Bolts",_Z="All Resistances +%d",VZ="+%d to All Skill Levels",JZ="+%d fire damage",QZ="Adds %d-%d fire damage",KZ="+%d cold damage",YZ="Adds %d-%d cold damage",XZ="+%d lightning damage",$Z="Adds %d-%d lightning damage",ZZ="+%d magic damage",eee="Adds %d-%d magic damage",aee="+%d poison damage over %d seconds",ree="Adds %d-%d poison damage over %d seconds",iee="+%d damage",nee="Adds %d-%d damage",lee="Enhanced damage",tee="Can Be Inserted in Socketed",oee="Weapons, Shields or Helms",see=`Helm: adds to strength
Shield: adds to shield's defense rating
Weapon: adds to attack rating
`,cee=`Helm: adds to maximum mana
Shield: adds resistance to cold
Weapon: adds cold damage to attack
`,mee=`Helm: adds to dexterity
Shield: adds resistance to poison
Weapon: adds poison damage to attack
`,pee=`Helm: adds to maximum life
Shield: adds resistance to fire
Weapon: adds fire damage to attack
`,dee=`Helm: adds to attack rating
Shield: adds to all resistances
Weapon: adds to damage vs. undead
`,uee=`Helm: adds to chance to find magic items
Shield: adds resistance to lightning
Weapon: adds lightning damage to attack
`,gee=`Helm: adds mana and life regeneration
Shield: adds attacker takes damage
Weapon: adds mana and life steal to attack
`,Mee=" dropped due to timeout.",hee=" dropped due to errors.",vee="%s joined our world. Diablo's minions grow stronger.",Hee="%s left our world. Diablo's minions weaken.",bee="%s(%s) joined our world. Diablo's minions grow stronger.",Aee="%s(%s) left our world. Diablo's minions weaken.",xee=" is not in the game.",Nee=" is not logged in.",fee=" was slain by ",kee=" was slain by ",Cee=" was slain.",yee="Wrong type of Gem.",Lee="Realm is going down in %d minutes.",Tee=" is not listening to you.",See="Player",wee=" whispers: ",Dee=" shouts: ",Pee=" )",Iee="\xFFc0You whispered to \xFFc1%s\xFFc0: %s",Eee="Working...",Ree="Null Shrine",Bee="Refilling Shrine",qee="Health Shrine",Gee="Mana Shrine",Uee="Health Exchange Shrine",Oee="Mana Exchange Shrine",zee="Armor Shrine",Fee="Combat Shrine",Wee="Resist Fire Shrine",jee="Resist Cold Shrine",_ee="Resist Lightning Shrine",Vee="Resist Poison Shrine",Jee="Skill Shrine",Qee="Mana Recharge Shrine",Kee="Stamina Shrine",Yee="Experience Shrine",Xee="Enirhs Shrine",$ee="Portal Shrine",Zee="Gem Shrine",eae="Fire Shrine",aae="Monster Shrine",rae="Exploding Shrine",iae="Poison Shrine",nae="You feel nothing.",lae="You feel refreshed.",tae="You feel healthy.",oae="You feel recharged.",sae="You feel incredibly healthy.",cae="You feel infused with energy.",mae="Your skin hardens.",pae="You feel ready for battle.",dae="You no longer fear fire.",uae="You no longer fear cold.",gae="You no longer fear lightning.",Mae="You no longer fear poison.",hae="You feel more skillful.",vae="Your spiritual force recovers quickly.",Hae="The weight of the world seems lighter.",bae="Your experience teaches you well.",Aae="Your sense of identity is subtly changed.",xae="The freedom to go home...",Nae="A marvelous gem...",fae="A fiery death...",kae="Death's advocate approaches.",Cae="A circle of flame...",yae="A circle of death...",Lae="Activate the stones in",Tae="this order.",Sae="The Horadric Malus has been returned to the Monastery.",wae="The scroll of Inifuss has been returned to the Tree.",Dae="The minions of Diablo have taken back Lam Esen's Tome.",Pae="The Townspeople",Iae="introduction",Eae="Act 1 Prologue",Rae="Den of Evil",Bae="Sisters' Burial Grounds",qae="Tools of the Trade",Gae="The Search for Cain",Uae="The Forgotten Tower",Oae="Sisters to the Slaughter",zae="Speech",Fae="New Entry",Wae="Quest Status",jae="No active quests.",_ae="Invalid Quest Value",Vae="Invalid State",Jae="Quest completed.",Qae="You cannot complete this quest in this game. Another player completed it first.",Kae="You completed this quest in a previous game.",Yae="You cannot complete this quest in this game. You can complete it by creating a new game.",Xae="You cannot complete this quest in this game. You can complete it by creating a new game or joining a different game.",$ae="You cannot complete this quest in this game. Cain was rescued without your help.",Zae="You must be level 8 to complete this quest. You can complete it by creating a new game or joining a different game when you are at least level 8.",ere="The person with the malus quit the game.",are="The person with the horadric scroll quit the game.",rre="Look for the Den in the wilderness outside the Rogues' Camp.",ire="Kill all the monsters in the Den.",nre="",lre="Monsters remaining: ",tre="One monster left.",ore="Return to Akara for a reward.",sre="Look for Blood Raven in the Burial Grounds next to the Cold Plains.",cre="Kill Blood Raven.",mre="Return to Kashya for a reward.",pre="Go through the Underground Passage to the Dark Wood, search for the Tree of Inifuss, and recover the Scroll.",dre="Take the Scroll of Inifuss to Akara.",ure="Go to the Cairn Stones in the Stony Field. Touch the Stones in the order found on the Scroll of Inifuss. Enter the portal to Tristram, but beware the danger that lies ahead.",gre="Find and rescue Deckard Cain.",Mre="Cain has been rescued and is now at the Rogue Encampment.",hre="Visit Cain and Akara in the Rogue Encampment.",vre="Talk to Akara for a reward.",Hre="Look for the Tower in the Black Marsh beyond the Dark Wood.",bre="Explore the cellar dungeons beneath the Tower ruins.",Are="Explore the cellar dungeons beneath the Tower ruins.",xre="Dispose of the evil Countess.",Nre="Look for the Horadric Malus in the Monastery Barracks. Beware of the Smith that guards it.",fre="Return the Horadric Malus to Charsi.",kre="Charsi will imbue an item with magical power.",Cre="Find Andariel's Lair in the depths of the Monastery Catacombs.",yre="Kill Andariel.",Lre="Return to Warriv to take the Caravan East.",Tre="Return to Warriv to take the Caravan East.",Sre="None",wre="Mouse 1",Dre="Mouse 2",Pre="Cancel",Ire="Mouse 3",Ere="Mouse 4",Rre="Mouse 5",Bre="Mouse Wheel Up",qre="Mouse Wheel Down",Gre="Kana",Ure="Junja",Ore="Final",zre="Kanji",Fre="Escape",Wre="Convert",jre="Non-Convert",_re="Accept",Vre="Mode Change",Jre="Left",Qre="Up",Kre="Right",Yre="Down",Xre="Select",$re="Execute",Zre="Left Windows",eie="Right Windows",aie="Apps Menu",rie="Num Lock",iie="Backspace",nie="Tab",lie="Clear",tie="Enter",oie="Shift",sie="Ctrl",cie="Alt",mie="Pause",pie="Caps Lock",die="Space",uie="Page Up",gie="Page Down",Mie="End",hie="Home",vie="P - Tell Ken",Hie="Print Screen",bie="Insert",Aie="Delete",xie="Help",Nie="Num Pad 0",fie="Num Pad 1",kie="Num Pad 2",Cie="Num Pad 3",yie="Num Pad 4",Lie="Num Pad 5",Tie="Num Pad 6",Sie="Num Pad 7",wie="Num Pad 8",Die="Num Pad 9",Pie="Num Pad *",Iie="Num Pad +",Eie="Separator",Rie="Num Pad -",Bie="Num Pad .",qie="Num Pad /",Gie="F1",Uie="F2",Oie="F3",zie="F4",Fie="F5",Wie="F6",jie="F7",_ie="F8",Vie="F9",Jie="F10",Qie="F11",Kie="F12",Yie="F13",Xie="F14",$ie="F15",Zie="F16",ene="F17",ane="F18",rne="F19",ine="F20",nne="F21",lne="F22",tne="F23",one="F24",sne="Scroll Lock",cne=";",mne="=",pne=",",dne="-",une=".",gne="/",Mne="~",hne="[",vne="\\",Hne="]",bne="'",Ane="m3",xne="m4",Nne="m5",fne="mwu",kne="mwd",Cne="kna",yne="jun",Lne="fin",Tne="kji",Sne="esc",wne="con",Dne="ncn",Pne="acc",Ine="mdc",Ene="lft",Rne="rgt",Bne="Dwn",qne="Slt",Gne="exc",Une="lwn",One="rwn",zne="apm",Fne="nml",Wne="bks",jne="clr",_ne="ent",Vne="sft",Jne="ctl",Qne="pse",Kne="clk",Yne="spc",Xne="pup",$ne="pdn",Zne="hme",ele="psn",ale="ins",rle="del",ile="hel",nle="np0",lle="np1",tle="np2",ole="np3",sle="np4",cle="np5",mle="np6",ple="np7",dle="np8",ule="np9",gle="slk",Mle="Option",hle="Command",vle="Opt",Hle="Cmd",ble="Function",Ale="Key/Button One",xle="Key/Button Two",Nle="Character Screen",fle="Inventory Screen",kle="Party Screen",Cle="Message Log",yle="Quest Log",Lle="Chat",Tle="Automap",Sle="Center Automap",wle="Micromap",Dle="Help Screen",Ple="Skill Tree",Ile="Skill Speed Bar",Ele="Skill 1",Rle="Skill 2",Ble="Skill 3",qle="Skill 4",Gle="Skill 5",Ule="Skill 6",Ole="Skill 7",zle="Skill 8",Fle="Select Previous Skill",Wle="Select Next Skill",jle="Show Belt",_le="Use Belt 1",Vle="Use Belt 2",Jle="Use Belt 3",Qle="Use Belt 4",Kle="Use Belt 5",Yle="Use Belt 6",Xle="Use Belt 7",$le="Use Belt 8",Zle="Use Belt 9",ete="Use Belt 10",ate="Use Belt 11",rte="Use Belt 12",ite="Say 'Help'",nte="Say 'Follow me'",lte="Say 'This is for you'",tte="Say 'Thanks'",ote="Say 'Sorry'",ste="Say 'Bye'",cte="Say 'Now you die'",mte="Run",pte="Toggle Run/Walk",dte="Stand Still",ute="Show Items",gte="Clear Screen",Mte="Screen Shot",hte="Default",vte="Accept",Hte="Cancel",bte="No keys were assigned because you neglected to assign one or more keys.",Ate="Keys assigned.",xte="Cannot assign to mouse button",Nte="Cannot assign to mouse wheel",fte="Cannot assign to this key",kte="Clear key",Cte="Clear Messages",yte="Show Portraits",Lte="Fade Automap",Tte="Names on Automap",Ste="Party on Automap",wte="New Stats",Dte="New Skill",Pte="Warps",Ite="No Warps",Ete="Choose your destination",Rte="No Other Waypoints Activated",Bte="MAX",qte="MAX",Gte="\xFFc",Ute=" ",Ote="-",zte=":",Fte=`
`,Wte="|",jte="/",_te="%",Vte="+",Jte="to",Qte="Players",Kte="Dwell",Yte="Larva",Xte="Barbarian",$te="Paladin",Zte="Necromancer",eoe="Sorceress",aoe="Amazon",roe="Druid",ioe="Assassin",noe="Nest",loe="No Party",toe="Party  #",ooe="imbue",soe="No Magic, Socketed, Rare, Unique, or Set Items. No Jewelry or Throwing Weapons.",coe="Use Gem",moe="Identify Items",poe="Identify Items: ",doe="Cannot repair unidentified items",uoe=" permits you to loot his corpse.",goe=" permits you to loot her corpse.",Moe=" has expressed hostility towards you.",hoe=" is no longer hostile towards you.",voe=" invites you to ally against the forces of evil.",Hoe=" has cancelled the party invite.",boe=" has joined your party to fight the forces of evil.",Aoe="You are now allied with ",xoe=" has left your party.",Noe="How much Gold would you like to drop?",foe="Drop Gold",koe="Message Log",Coe="Armor",yoe="Weapons",Loe="Magic",Toe="Misc",Soe="trade",woe="accept trade",Doe="agree to trade",Poe="asking other player to trade",Ioe=" is busy",Eoe="One of you has too much stuff",Roe="How much Gold would you like to offer?",Boe="You must wait a short time to trade with that player.",qoe=": ",Goe="How much Gold would you like to deposit?",Uoe="How much Gold would you like to withdraw?",Ooe="Gold Max: %d",zoe="Golem",Foe="Skeleton",Woe="Mage",joe="Revived",_oe="Valkyrie",Voe="Level",Joe="Experience",Qoe="Next Level",Koe="Strength",Yoe="Damage",Xoe="Dexterity",$oe=`%s
Attack Rating`,Zoe="Defense",ese=`%s
Rating`,ase="Vitality",rse="Stamina",ise="Life",nse="Energy",lse="Mana",tse=`Fire
Resistance`,ose=`Cold
Resistance`,sse=`Lightning
Resistance`,cse=`Poison
Resistance`,mse="Stat Points",pse="Remaining",dse="Mace Class",use="Axe Class",gse="Sword Class",Mse="Dagger Class",hse="Equip to Throw",vse="Javelin Class",Hse="Spear Class",bse="Bow Class",Ase="Staff Class",xse="Polearm Class",Nse="Crossbow Class",fse="Fastest Attack Speed",kse="Very Fast Attack Speed",Cse="Fast Attack Speed",yse="Normal Attack Speed",Lse="Slow Attack Speed",Tse="Very Slow Attack Speed",Sse="Slowest Attack Speed",wse="(Necromancer Only)",Dse="(Paladin Only)",Pse="(Sorceress Only)",Ise="Damage to Undead",Ese="Gold",Rse="Invite this player ",Bse="to join your party.",qse="Accept this player's ",Gse="invitation to form a party.",Use="Cancel your invitation",Ose="to this player.",zse="Click to go hostile",Fse="with this player.",Wse="Click to go neutral",jse="with this player.",_se="Click to allow this player",Vse="to loot your corpse.",Jse="Click to disallow this player",Qse="from looting your corpse.",Kse="Click to allow this player",Yse="to hear you.",Xse="Click to stop this player",$se="from hearing you.",Zse="Click to squelch this player.",e1e="Click to un-squelch this player.",a1e="Remove yourself from party.",r1e="Must be toggled in town.",i1e="Both players must be at least level 9",n1e="to go hostile with each other",l1e="Withdraw",t1e="Drop Gold",o1e="Deposit",s1e="Offer",c1e="Gold in Stash:",m1e="Trade Gold",p1e="Cancel",d1e="ACCEPT TRADE",u1e="The True Tomb is Hidden.",g1e=" has items in his box.",M1e="You have items in your box.",h1e=" - Free for you",v1e="Act 1",H1e="Act 2",b1e="Act 3",A1e="Act 4",x1e="Level",N1e="cancel",f1e="close",k1e="Close",C1e="In your party",y1e="In a party",L1e="INVITE",T1e="ACCEPT",S1e="LEAVE",w1e="CLOSE",D1e="Amazon",P1e="Sorceress",I1e="Barbarian",E1e="Necromancer",R1e="Paladin",B1e="Average chance to hit",q1e="level %d monster: %d%%",G1e="Average chance a level %d",U1e="monster will hit you: %d%%",O1e="Experience: %u / %u",z1e="Stamina: %d / %d",F1e="Life: %d / %d",W1e="Mana: %d / %d",j1e="Open Mini Panel",_1e="Close Mini Panel",V1e="Character",J1e="Inventory",Q1e="Skill Tree",K1e="Party Screen",Y1e="Automap",X1e="Message Log",$1e="Quest Log",Z1e="Game Menu (Esc)",e0e="Help",a0e=" (%s)",r0e="Run",i0e="Walk",n0e="Game: ",l0e="Password: ",t0e="Difficulty: %s",o0e="Quantity : %d",s0e="Level ",c0e=" percent",m0e="Required Level : ",p0e="Quantity ",d0e="Char Info",u0e="Quests",g0e="Unused",M0e="Inventory",h0e="Menu",v0e="Automap",H0e="Unused",b0e="Skill Tree",A0e="Your stash is full.",x0e="Diablo II Help",N0e="Hold Down <%s> to Run",f0e="Hold down <%s> to highlight items on the ground",k0e="Hold down <%s> to attack while standing still",C0e="Hit <%s> to toggle the automap on and off",y0e="Hit <Esc> to bring up the Game Menu",L0e="Hit <Enter> to go into chat mode",T0e="Use F1-F8 to set your Left or Right Mouse Button Skills.",S0e="Hit <%s> to toggle this screen open and closed",w0e="Life Orb",D0e="Left Mouse-",P0e="Button Skill",I0e="(Click to Change)",E0e="Right Mouse-",R0e="Run/Walk",B0e="Toggle",q0e="Stamina Bar",G0e="Experience",U0e="Bar",O0e="Mini-Panel",z0e="(opens Character,",F0e="Inventory, and",W0e="other screens)",j0e="Belt",_0e="Mana Orb",V0e="",J0e="Skill Tab 1",Q0e="Skill Tab 2",K0e="Skill Tab 3",Y0e="Skill",X0e="Choices",$0e="Remaining",Z0e="Skills",e5e="Spells",a5e="Javelin",r5e="and Spear",i5e="Passive",n5e="and Magic",l5e="Bow and",t5e="Crossbow",o5e="Defensive",s5e="Auras",c5e="Offensive",m5e="Combat",p5e="Summoning",d5e="Poison",u5e="and Bone",g5e="Curses",M5e="Warcries",h5e="Combat",v5e="Masteries",H5e="Cold",b5e="Lightning",A5e="Fire",x5e="",N5e="Next Level",f5e="Current Skill Level: ",k5e="Mana Cost: ",C5e="Damage: ",y5e="Fire Damage: ",L5e="Cold Damage: ",T5e="Lightning Damage: ",S5e="Poison Damage: ",w5e=" arrows",D5e="To Attack Rating: ",P5e=" hits",I5e="-",E5e="Cold Length: ",R5e="Poison Length: ",B5e=" second",q5e=" seconds",G5e="First Level",U5e="Radius: ",O5e=" squares",z5e="Duration: ",F5e="Defense: ",W5e="Attack: ",j5e=" percent",_5e=" percent chance",V5e="Enemy Defense: ",J5e=" yards",Q5e=" bolts",K5e=" teeth",Y5e="Freeze Length: ",X5e="Attack Bonus: ",$5e="Defense Bonus: ",Z5e="Fire Damage",ece="Weakens Enemies by ",ace=" per second",rce="Continuous Fire Damage: ",ice=" yard",nce="Damage Taken: ",lce="Target's Damage: ",tce="Magic Damage: ",oce="Absorbs ",sce=" damage",cce="Life: ",mce=" skeleton mage",pce=" skeleton magi",dce="Golem Level: ",uce=" percent of corpse Life",gce=" damage to Self",Mce="Stun Length: ",hce=" percent of shield strength",vce="Heals: ",Hce="Resist Fire: ",bce="Resist Cold: ",Ace="Resist Lightning: ",xce="Resist All: ",Nce=" percent damage returned",fce="Range: ",kce="Target's Attack: ",Cce="Enemy runs up to ",yce="Enemy runs for ",Lce=" per target",Tce="Multiple Hits",Sce="Freezes for ",wce="over ",Dce=" poison damage",Pce="Chance of losing durability: ",Ice="Target stutters for ",Ece="Ranged attacks slowed to ",Rce="Average ",Bce="Stamina Recovery Rate: ",qce="Velocity: ",Gce="Stamina Bonus: ",Uce="Releases ",Oce=" charged bolts",zce="Duration reduced by ",Fce="Elemental Damages: ",Wce="Chance uninterruptable ",jce="Enemies slowed ",_ce="Remains target for ",Vce=" percent of attack damage",Jce="Converts ",Qce=" percent damage to life",Kce="Fire Duration: ",Yce="Fire Explosion Damage: ",Xce="Lightning Bolt Damage: ",$ce="Reduces curse duration by ",Zce="Attacks up to ",e2e=" targets",a2e="Mana Recovery Rate: ",r2e="Walk/Run Speed: ",i2e="Resistances: ",n2e="Holy Bolt Damage: ",l2e=" mana per knockback",t2e=" skeleton total",o2e="Skeletons: ",s2e="Magi: ",c2e="Monsters: ",m2e="Lowers Maximum Resistances ",p2e="Chance to convert: ",d2e="Max Life: ",u2e="Max Mana: ",g2e="Max Stamina: ",M2e=" percent fire damage",h2e=" monster",v2e=" monsters",H2e="Attack Speed: ",b2e="Life/Mana Recovered: ",A2e=" points",x2e="Chance to redeem soul: ",N2e="Successful Blocking: ",f2e=" per yard",k2e="Thorns damage",C2e="Hydra Fire Damage: ",y2e="Resist Elemental Damage: ",L2e="Minimum Mana Required to Cast: ",T2e="Maximum Level Reached",S2e=" (item)",w2e="You have been granted this skill by an item",D2e="You have not learned this skill yet",P2e="Attack",I2e="normal attack",E2e="normal attack",R2e="Attack",B2e="Kick",q2e="kick target",G2e="kick target",U2e="kick target",O2e="Throw",z2e="throw equipped item",F2e="throw equipped item",W2e="Throw",j2e="Unsummon",_2e="releases a summoned creature",V2e=`of one of your creatures
relinquishes control`,J2e="Unsummon",Q2e="Left Hand Throw",K2e="throw left hand item",Y2e="throw left hand item",X2e="Left Throw",$2e="Left Hand Swing",Z2e="swing left hand weapon",eme="swing left hand weapon",ame="Left Swing",rme="Magic Arrow",ime="creates a magical arrow",nme=`that does extra damage
creates a magical arrow or bolt`,lme="Magic Arrow",tme="Fire Arrow",ome="enchants arrows with flame",sme=`always hits
or bolts with fire
magically enhances your arrows`,cme="Fire Arrow",mme="Inner Sight",pme="illuminates and weakens nearby monsters",dme=`for you and your party
making them easier to hit
illuminates nearby enemies`,ume="Inner Sight",gme="Critical Strike",Mme="passive - chance of doing double damage",hme="passive - your attacks have a chance to do double damage",vme="Critical Strike",Hme="Jab",bme="rapid attacks with a thrusting weapon",Ame=`using a javelin or spear class weapon
attacks with a series of rapid thrusts`,xme="Jab",Nme="Cold Arrow",fme="enchants arrows to slow targets",kme=`always hits
cold arrows only do half of their regular damage
by adding cold damage and a slowing effect
magically enhances your arrows or bolts`,Cme="Cold Arrow",yme="Multiple Shot",Lme="fires multiple arrows",Tme=`or bolt into many
magically splits one arrow`,Sme="Multiple Shot",wme="Dodge",Dme="passive - dodges melee attacks",Pme=`or standing still
a melee attack when attacking
passive - you have a chance to dodge`,Ime="Dodge",Eme="Power Strike",Rme="adds lightning damage",Bme=`javelin and spear class weapons
adds lightning damage to attacks with`,qme="Power Strike",Gme="Poison Javelin",Ume="adds poison damage",Ome=`to leave a trail of poison clouds
magically enhances your javelin`,zme="Poison Javelin",Fme="Exploding Arrow",Wme="enchant arrows to explode",jme=`always hits
contact, damaging all nearby enemies
enchants an arrow or bolt that explodes on`,_me="Exploding",Vme="Slow Missiles",Jme="slows ranged attacks of enemies",Qme="illuminates nearby enemies and slows their ranged attacks",Kme="Slow Missiles",Yme="Avoid",Xme="passive - dodges missiles",$me=`when attacking or standing still
passive - you have a chance to dodge enemy missiles`,Zme="Avoid",epe="Impale",ape="increases damage but degrades weapon",rpe="increases attack damage but rapidly degrades the weapon",ipe="Impale",npe="Lightning Bolt",lpe="changes a thrown javelin into lightning",tpe="magically converts your javelin into a bolt of lightning",ope="Lightning Bolt",spe="Ice Arrow",cpe="enchants arrows to freeze enemies",mpe=`always hits
to freeze your enemies
magically enhances your arrow or bolt`,ppe="Ice Arrow",dpe="Guided Arrow",upe="enchants arrows to seek enemies",gpe=`always hits
or seek one of its own
to track your target
enhances your arrows and bolts`,Mpe="Guided Arrow",hpe="Penetrate",vpe="passive - increases attack rating",Hpe="passive - increases your attack rating",bpe="Penetrate",Ape="Charged Strike",xpe="enchants thrusting weapons with charged bolts",Npe=`and releases charged bolts upon impact
adds lightning damage to javelin and spear class weapons`,fpe="Charged Strike",kpe="Plague Javelin",Cpe="enchants javelins with poison explosions",ype=`expanding clouds of poison upon impact
magically enhances your javelin to release`,Lpe="Plague Javelin",Tpe="Strafe",Spe="enchants arrows to strike multiple targets",wpe=`that target multiple nearby enemies
magically splits one arrow into several`,Dpe="Strafe",Ppe="Immolation Arrow",Ipe="enchants arrows to burn enemies",Epe=`always hits
creates a pyre upon impact
cause severe fire damage and
enhances arrows or bolts to`,Rpe="Immolation",Bpe="Decoy",qpe="creates a duplicate of yourself",Gpe=`that draws fire from enemies
creates a duplicate of yourself`,Upe="Decoy",Ope="Evade",zpe="passive - dodges when moving",Fpe=`when walking or running
a melee or missile attack
passive - you have a chance to dodge`,Wpe="Evade",jpe="Fend",_pe="attacks all adjacent targets",Vpe="attacks all adjacent targets",Jpe="Fend",Qpe="Freezing Arrow",Kpe="enchants arrows to freeze multiple monsters",Ype=`always hits
to freeze entire groups of monsters
magically enhances an arrow or bolt`,Xpe="Freezing Arrow",$pe="Valkyrie",Zpe="summons a powerful Valkyrie ally",ede="summons a powerful Valkyrie ally",ade="Valkyrie",rde="Pierce",ide="passive - missiles may continue through enemies",nde=`pass through enemies that they hit
passive - your missiles have a chance to`,lde="Pierce",tde="Lightning Strike",ode="enchants thrusting weapons with chain lightning",sde=`and releases chain lightning upon impact
adds lightning damage to javelin and spear class weapons`,cde="Light'ng Strike",mde="Lightning Fury",pde="a lightning bolt that splits on impact",dde=`bolt of lightning that splits on impact
changes a thrown javelin into a powerful`,ude="Lightning Fury",gde="Fire Bolt",Mde="creates a missile of flame",hde="creates a magical flaming missile",vde="Fire Bolt",Hde="Warmth",bde="passive - increases mana recovery rate",Ade="passive - increases the rate at which you recover mana",xde="Warmth",Nde="Charged Bolt",fde="creates multiple deadly sparks",kde=`bolts of electrical energy
creates multiple, randomly directed`,Cde="Charged Bolt",yde="Ice Bolt",Lde="creates a shard of ice that slows enemies",Tde=`that damages and slows your enemies
creates a magical bolt of ice`,Sde="Ice Bolt",wde="Frozen Armor",Dde="improves defense and freezes attacker",Pde=`and freezes enemies that hit you
increases your defense rating`,Ide="Frozen Armor",Ede="Inferno",Rde="creates a jet of flame",Bde=`to scorch your enemies
creates a continuous jet of flame`,qde="Inferno",Gde="Static Field",Ude="creates a field of deadly sparks",Ode=`of all nearby enemies
creates an electrical field that reduces life`,zde="Static Field",Fde="Telekinesis",Wde="moves objects with your mind",jde=`and knock back enemies
pick up items, use objects,
uses the power of your mind to`,_de="Telekinesis",Vde="Frost Nova",Jde="creates a freezing ring",Qde=`and slows all nearby enemies
creates an expanding ring of ice that damages`,Kde="Frost Nova",Yde="Ice Blast",Xde="creates an ice bolt that freezes enemies",$de=`damages and freezes your enemy
creates a magical sphere of ice that`,Zde="Ice Blast",eue="Blaze",aue="creates fire in your wake",rue=`in your wake to scorch your enemies
creates a wall of fire`,iue="Blaze",nue="Fire Ball",lue="creates an explosive sphere of fire",tue=`to engulf your enemies
creates an explosive sphere of fiery death`,oue="Fire Ball",sue="Nova",cue="creates an electrically charged ring",mue=`to shock nearby enemies
creates an expanding ring of lightning`,pue="Nova",due="Lightning",uue="creates a bolt of lightning",gue=`to lay waste to your enemies
creates a powerful lightning bolt`,Mue="Lightning",hue="Shiver Armor",vue="freezes and damages attackers",Hue=`freezes and damages enemies that hit you
increases your defense rating`,bue="Shiver Armor",Aue="Fire Wall",xue="creates a wall of flame",Nue=`blocks or burns your enemies
creates a wall of flame that`,fue="Fire Wall",kue="Enchant",Cue="enchants melee or ranged weapons with fire",yue=`adds one-third fire damage to ranged weapons
adds fire damage to melee weapons
enchants equipped weapon of targeted character or minion`,Lue="Enchant",Tue="Chain Lightning",Sue="creates a bolt of lightning that arcs",wue=`arcs through several targets
creates a bolt of lightning that`,Due="Chain Lightning",Pue="Teleport",Iue="instantly moves to destination",Eue="instantly moves to a destination within your line of sight",Rue="Teleport",Bue="Glacial Spike",que="creates a freezing comet of ice",Gue=`that freezes or kills nearby enemies
creates a magical ice comet`,Uue="Glacial Spike",Oue="Meteor",zue="summons a meteor from the heavens",Fue=`to crush and incinerate your enemies
summons a meteor from the heavens`,Wue="Meteor",jue="Thunder Storm",_ue="summons a powerful tempest",Vue=`your enemies with bolts of lightning
summons a deadly thunderstorm that strikes`,Jue="Thunder Storm",Que="Energy Shield",Kue="uses your mana as a shield",Yue=`instead of health when you take damage
creates a magical shield that consumes mana`,Xue="Energy Shield",$ue="Blizzard",Zue="summons a massive ice storm",e3e="summons massive shards of ice to destroy your enemies",a3e="Blizzard",r3e="Chilling Armor",i3e="retaliates against ranged attackers",n3e=`against ranged attackers
increases defense and discharges an ice bolt in retaliation`,l3e="Chill'n Armor",t3e="Fire Mastery",o3e="passive - increases fire damage",s3e="passive - increases all damage caused by your fire spells",c3e="Fire Mastery",m3e="Hydra",p3e="summons multi-headed fire beast",d3e=`to reduce your enemies to ashes
summons a multi-headed beast of flame`,u3e="Hydra",g3e="Lightning Mastery",M3e="passive - reduces cost of lightning spells",h3e=`to cast your lightning spells
passive - reduces the mana required`,v3e="Lightning Mastery",H3e="Frozen Orb",b3e="creates a globe of frozen death",A3e=`to lay waste to your enemies
creates a magical globe that sprays a torrent of ice bolts`,x3e="Frozen Orb",N3e="Cold Mastery",f3e="passive - cold attacks become piercing",k3e=`by piercing enemies' resistances to cold
passive - increases the damage of your cold attacks`,C3e="Cold Mastery",y3e="Amplify Damage",L3e="curse - amplifies damage taken by enemies",T3e=`the non-magic damage they receive
curses a group of enemies, increasing`,S3e="Amplify",w3e="Teeth",D3e="fires barbed teeth",P3e="fires a barrage of summoned barbed teeth",I3e="Teeth",E3e="Bone Armor",R3e="creates a damage absorbing bone shell",B3e=`that absorbs melee damage
creates an orbiting shield of bone`,q3e="Bone Armor",G3e="Skeleton Mastery",U3e="passive - better skeletons and revived creatures",O3e=`of raised skeletons and revived creatures
passive - increases life and damage`,z3e="Skeleton Mastery",F3e="Raise Skeleton",W3e="reanimate skeletal warrior from target corpse",j3e=`fights for you
this raises a skeleton warrior that
cast on the corpse of a slain monster,`,_3e="Raise Skeleton",V3e="Dim Vision",J3e="curse - reduces vision of monsters",Q3e=`reducing their vision radius
curses a group of monsters,`,K3e="Dim Vision",Y3e="Weaken",X3e="curse - reduces damage done by enemies",$3e=`reducing the amount of damage they inflict
curses a group of enemies,`,Z3e="Weaken",ege="Poison Dagger",age="next dagger attack poisons target",rge="adds poison to your dagger attacks",ige="Poison Dagger",nge="Corpse Explosion",lge="turns a corpse into a bomb",tge=`it explodes, damaging nearby enemies
cast on the corpse of a slain monster,`,oge="Corpse Exp.",sge="Clay Golem",cge="creates a golem to fight for you",mge=`to fight by your side
creates a golem from the earth`,pge="Clay Golem",dge="Iron Maiden",uge="curse - enemies damage themselves",gge=`to damage themselves when damaging others
curses a group of enemies, causing them`,Mge="Iron Maiden",hge="Terror",vge="curse - monsters run away in fear",Hge=`causing them to flee in terror
curses a group of monsters,`,bge="Terror",Age="Bone Wall",xge="creates an impassable barrier",Nge=`of bone and debris
creates an impassable barrier`,fge="Bone Wall",kge="Golem Mastery",Cge="Enhances Speed and Life of Golems",yge="Enhances Speed and Life of all your Golems",Lge="Golem Mastery",Tge="Raise Skeletal Mage",Sge="reanimate skeletal mage from target corpse",wge=`fights for you
this raises a skeleton mage that
cast on the corpse of a slain monster,`,Dge="Skeletal Mage",Pge="Confuse",Ige="curse - monster attacks random targets",Ege="curses a monster to force it to attack random targets",Rge="Confuse",Bge="Life Tap",qge="curse - enemies return life to attacker",Gge=`damaging them gives the attacker life
curses a group of monsters so that`,Uge="Life Tap",Oge="Poison Explosion",zge="turns a corpse into a poison gas bomb",Fge=`that poisons nearby monsters
toxic gas is released
cast on the corpse of a slain monster,`,Wge="Poison Exp.",jge="Bone Spear",_ge="summons a deadly spike of bone",Vge="summons a deadly spike of bone to impale your enemies",Jge="Bone Spear",Qge="Blood Golem",Kge="a golem that shares life and damage",Yge=`it steals and damage it receives
creates a golem that shares with you the life`,Xge="Blood Golem",$ge="Attract",Zge="curse - monster becomes universal target",eMe=`this curse may not be overridden by another curse
target of all nearby monsters
curses a monster to becomes the`,aMe="Attract",rMe="Decrepify",iMe="curse - greatly slows and weakens enemies",nMe=`slow, weak and take amplified damage
curses a group of enemies to make them`,lMe="Decrepify",tMe="Bone Prison",oMe="creates a barrier of bone around target",sMe="creates a barrier of fossilized bone around your target",cMe="Bone Prison",mMe="Summon Resist",pMe="passive - summoned monsters gain resistances",dMe=`of all summoned creatures
passive - increases the resistances`,uMe="Summon Resist",gMe="Iron Golem",MMe="creates a golem from an item",hMe=`the properties of the item
transforms a metallic item into a golem that gains`,vMe="Iron Golem",HMe="Lower Resist",bMe="curse - lowers enemies resistance to magic",AMe=`lowers maximum resistances of hostile players
lowers resistances of monsters
curses an enemy to take more damage from all magical attacks`,xMe="Lower Resist",NMe="Poison Nova",fMe="emits an expanding ring of poison",kMe="emits an expanding ring of concentrated poison",CMe="Poison Nova",yMe="Bone Spirit",LMe="releases an undead specter",TMe=`tracks its target or finds one of its own
releases a spirit of the restless undead that`,SMe="Bone Spirit",wMe="Fire Golem",DMe="creates a golem of fire",PMe=`it receives from fire into life
creates a golem that converts the damage`,IMe="Fire Golem",EMe="Revive",RMe="raises a monster to fight for you",BMe=`to fight by your side
returns a monster to life`,qMe="Revive",GMe="Sacrifice",UMe="increased accuracy and damage",OMe=`at the cost of life
increased accuracy and damage`,zMe="Sacrifice",FMe="Smite",WMe="shield bash",jMe=`by bashing it with your shield
temporarily stun your enemy`,_Me="Smite",VMe="Might",JMe="aura - increases damage",QMe=`done by you and your party
when active, aura increases the damage`,KMe="Might",YMe="Prayer",XMe="aura - regenerates life",$Me=`the life of you and your party
when active, aura slowly regenerates`,ZMe="Prayer",ehe="Resist Fire",ahe="aura - protects against fire damage",rhe=`done to you and your party
when active, aura decreases fire damage`,ihe="Resist Fire",nhe="Holy Bolt",lhe="divine energy that damages undead",the=`or heals allies
that damages undead enemies
a bolt of divine energy`,ohe="Holy Bolt",she="Holy Fire",che="aura - flames damage nearby enemies",mhe=`with heavenly flames
when active, aura damages nearby enemies`,phe="Holy Fire",dhe="Thorns",uhe="aura - reflects damage back at enemies",ghe=`back at your attacker
when active, aura reflects damage done to you`,Mhe="Thorns",hhe="Defiance",vhe="aura - increases defense",Hhe=`of you and your party
when active, aura increases the defense rating`,bhe="Defiance",Ahe="Resist Cold",xhe="aura - protects against cold damage",Nhe=`done to you and your party
when active, aura decreases cold damage`,fhe="Resist Cold",khe="Zeal",Che="attacks multiple adjacent enemies",yhe=`with a single attack
allows you to attack multiple adjacent enemies`,Lhe="Zeal",The="Charge",She="charge and attack target",whe="charge into battle and attack an enemy",Dhe="Charge",Phe="Blessed Aim",Ihe="aura - increases your attack rating",Ehe=`for you and your party
when active, aura increases the attack rating`,Rhe="Blessed Aim",Bhe="Cleansing",qhe="aura - reduces poison and curse duration",Ghe=`will remain poisoned or cursed
of time you and your party
when active, aura reduces the length`,Uhe="Cleansing",Ohe="Resist Lightning",zhe="aura - protects against lightning damage",Fhe=`done to you and your party
when active, aura decreases lightning damage`,Whe="R. Lightning",jhe="Vengeance",_he="attacks add elemental damage",Vhe=`to each successful attack
fire, lightning and cold damage are added`,Jhe="Vengeance",Qhe="Blessed Hammer",Khe="summon a spiraling magic hammer",Yhe=`150 Percent Damage to Undead
spirals outwards damaging enemies it hits
summons an ethereal hammer that`,Xhe="B. Hammer",$he="Concentration",Zhe="aura - increases your attack ability",e4e=`that the attack will be interrupted for you and your party 
when active, aura increases the damage and decreases the chance`,a4e="Concentration",r4e="Holy Freeze",i4e="aura - freezes nearby monsters",n4e="when active, aura freezes nearby monsters",l4e="Holy Freeze",t4e="Vigor",o4e="aura - increases speed and stamina recovery",s4e=`and movement speed for you and your party
when active, aura increases stamina recovery rate, maximum stamina`,c4e="Vigor",m4e="Conversion",p4e="Change allegiance of monsters",d4e=`other foul demons and beasts
converts monsters to fight against`,u4e="Conversion",g4e="Holy Shield",M4e="enhances your shield",h4e="enhances your shield with divine power",v4e="Holy Shield",H4e="Holy Shock",b4e="aura - lightning damages nearby enemies",A4e=`to damage nearby enemies
when active, aura causes pulses of electricity`,x4e="Holy Shock",N4e="Sanctuary",f4e="aura - repels and damages undead",k4e=`and knocks them back
when active, aura damages the undead`,C4e="Sanctuary",y4e="Meditation",L4e="aura - increases mana recovery",T4e=`for you and your party
when active, aura increases mana recovery`,S4e="Meditation",w4e="Fist of the Heavens",D4e="target is banished",P4e=`seek out nearby enemies
lightning strikes your target as holy bolts`,I4e="Heaven's Fist",E4e="Fanaticism",R4e="aura - increases attack speed",B4e=`and attack rating for you and your party
when active, aura increases attack speed`,q4e="Fanaticism",G4e="Conviction",U4e="aura  - weakens enemies",O4e=`and resistances of nearby enemies
when active, aura reduces the defenses`,z4e="Conviction",F4e="Redemption",W4e="aura - redeems the dead for mana and life",j4e=`life and mana to you and your party
the souls of slain enemies to give
when active, aura attempts to redeem`,_4e="Redemption",V4e="Salvation",J4e="aura - protects against elemental damage",Q4e=`done to you and your party
when active, aura decreases fire, cold and lightning damage`,K4e="Salvation",Y4e="Bash",X4e="powerful blow that increases damage",$4e=`to enemies and knocks them back
powerful blow that increases the damage done`,Z4e="Bash",eve="Sword Mastery",ave="passive - improves sword fighting skill",rve="passive - improves sword fighting skill",ive="Sword Mastery",nve="Axe Mastery",lve="passive - improves axe fighting skill",tve="passive - improves axe fighting skill",ove="Axe Mastery",sve="Mace Mastery",cve="passive - improves mace fighting skill",mve="passive - improves mace fighting skill",pve="Mace Mastery",dve="Howl",uve="frightens nearby monsters",gve=`scrambling away in fear
sends nearby monsters`,Mve="Howl",hve="Find Potion",vve="targets corpses to find potions",Hve=`for a chance to find a potion
use on the corpse of a slain monster`,bve="Find Potion",Ave="Leap",xve="jumps over obstacles",Nve=`or into the fray
leaps away from danger`,fve="Leap",kve="Double Swing",Cve="swings two weapons at once",yve=`or one target twice
attacks two targets if possible,
when two weapons are equipped`,Lve="Double Swing",Tve="Pole Arm Mastery",Sve="passive - improves pole arm skill",wve="passive - improves pole arm skill",Dve="Pole Arm Mastery",Pve="Throwing Mastery",Ive="passive - improves thrown weapon skill",Eve="passive - improves thrown weapon skill",Rve="Throwing Mastery",Bve="Spear Mastery",qve="passive - improves spear fighting skill",Gve="passive - improves spear fighting skill",Uve="Spear Mastery",Ove="Taunt",zve="causes a monster to attack",Fve="enrages a monster into relentlessly attacking",Wve="Taunt",jve="Shout",_ve="alerts party and improves defense",Vve=`rating of you and your party
warns of impending danger and improves the defense`,Jve="Shout",Qve="Stun",Kve="stuns your target",Yve=`and increases your attack rating
stuns your target for a short time`,Xve="Stun",$ve="Double Throw",Zve="throw two weapons at once",eHe=`throwing weapons at the same time
allows you to throw two different`,aHe="Double Throw",rHe="Increased Stamina",iHe="passive - increases stamina",nHe="passive - increases your stamina",lHe="Increased Stamina",tHe="Find Item",oHe="targets corpses to find items",sHe=`to find hidden treasures
use on the corpse of a slain monster`,cHe="Find Item",mHe="Leap Attack",pHe="leaps and attacks target enemy",dHe=`in one swift assault
leaps to and attacks target enemy`,uHe="Leap Attack",gHe="Concentrate",MHe="attack that is not interruptible",hHe=`improves attack and defense rating
attack that is not interruptible and`,vHe="Concentrate",HHe="Iron Skin",bHe="passive - improves defense rating",AHe="passive - improves defense rating",xHe="Iron Skin",NHe="Battle Cry",fHe="reduces enemy effectiveness",kHe=`enemies' defense rating and damage
fearsome cry that decreases`,CHe="Battle Cry",yHe="Frenzy",LHe="successful double swing hit increases speed",THe=`requires you to equip two weapons
each successful attack increases your overall speed
allows you to swing two weapons at once`,SHe="Frenzy",wHe="Increased Speed",DHe="passive - increases walk and run speed",PHe="passive - increases walk and run speed",IHe="Increased Speed",EHe="Battle Orders",RHe="improves life, mana and stamina of party",BHe=`stamina of you and your party
improves the maximum mana, life and`,qHe="Battle Orders",GHe="Grim Ward",UHe="creates a frightening totem",OHe=`that causes nearby monsters to flee
to create a frightening totem
use on the corpse of a slain monster`,zHe="Grim Ward",FHe="Whirlwind",WHe="whirling dance of death",jHe=`legions of your enemies
that cuts a path through the
a whirling dance of death`,_He="Whirlwind",VHe="Berserk",JHe="powerful but reckless attack",QHe=`but decreases defense rating
that increases damage and attack rating
a powerful but reckless attack`,KHe="Berserk",YHe="Natural Resistance",XHe="passive - increases natural resistances",$He=`to elemental and poison damage
passive - increases natural resistances`,ZHe="Natural Resistance",ebe="War Cry",abe="injures and stuns nearby enemies",rbe="injures and stuns all nearby enemies",ibe="War Cry",nbe="Battle Command",lbe="increases skill levels",tbe="increases all current skill levels for you and your party",obe="Battle Cmd",sbe="Scroll of Identify",cbe="identify a magic item's properties",mbe="identify a magic item's properties",pbe="Identify",dbe="Tome of Identify",ube="identify a magic item's properties",gbe="identify a magic item's properties",Mbe="Identify",hbe="Scroll of Townportal",vbe="create a magic portal to the nearest town",Hbe="create a magic portal to the nearest town",bbe="Townportal",Abe="Tome of Townportal",xbe="create a magic portal to the nearest town",Nbe="create a magic portal to the nearest town",fbe="Townportal",kbe="Ormus has the key that opens this door.",Cbe="Lady %s",ybe="Lord %s",Lbe="Hardcore",Tbe="Level %d",Sbe="Tristram",wbe="Cathedral",Dbe="Barracks",Pbe="Mausoleum",Ibe="Crypt",Ebe="Death takes its toll of %d Gold",Rbe="You have lost experience",Bbe="Your deeds of valor will be remembered",qbe="%d Seconds Until Game Ends",Gbe="Congratulations!",Ube="You Have Vanquished Diablo",Obe="Will Henceforth Be Known As",zbe="Unable to remove message filter.",Fbe="By logging on to Battle.net, you are certifying that you have read and agree to its current Terms of Service",Wbe="an evil force",jbe="an evil force",_be="an evil force",Vbe="Right click to make",Jbe="Not in Beta.",Qbe="No Level Name",Kbe="End of Beta",Ybe=`40
Praise be to the Light! You have 
accomplished the impossible!
 
Diablo and Mephisto have been 
banished back into the Black Abyss 
that spawned them, and the corrupted 
Soulstones are no more.
 
However, while you were fighting here, 
Baal remained behind in the mortal 
realm, building an army of hellish 
minions. Now, Baal's army is searching 
for the Worldstone, the ancient source 
of all the Soulstones and their power, 
while leaving behind a wake of 
destruction. They have forged deeply 
into the Barbarian homelands, heading 
directly for the summit of Mount 
Arreat!
 
Baal knows, mortal hero! That is the 
very site of the blessed Worldstone!
 
Now, enter the portal I have opened for 
you. It will take you to the Barbarian 
city of Harrogath, the last bastion of 
Order on the slopes of Arreat.
`,Xbe=`40
I knew there was great potential in you, 
my friend. You've done a fantastic job.
 
Though my ancestors often struggled 
against the Three Evils and their 
minions, I've always lived a shut-in, 
scholarly life. I'm glad that my wisdom 
aided you.
 
Now, I wish to leave this place. Though 
Heaven's Gates are a marvel to behold, 
I hope I won't have to see them again 
for many, many years.
 
Please talk to Tyrael about leaving this 
place now!
`,$be=`35
We are the spirits of the Nephalem, the 
Ancient Ones. We have been chosen to 
guard sacred Mount Arreat, wherein 
the Worldstone rests. Few are worthy 
to stand in its presence; fewer still can 
comprehend its true purpose.
 
Before you enter, you must defeat us.
`,Zbe=`39
I am amazed to find this place so 
untouched. Everything else in the path 
of Baal the Lord of Destruction lies in 
ruin. 
 
These Barbarians must indeed be the 
legendary guardians of Mount Arreat. 
They are a proud, hardy people. Don't 
expect to be greeted warmly -- 
strangers here rarely are.
 
Perhaps I can gain their trust. I'll spend 
some time with the townsfolk and try 
to understand them better. I'll let you 
know what I discover.
`,e6e=`52
With hellspawn, size is no measure of 
their threat. Demons half the size of 
men can kill with a gesture, while 
hellish pack animals trample any who 
stand in their way.
`,a6e=`55
Though these Barbarians are known 
throughout the kingdoms as ferocious 
fighters, they are also capable of great 
compassion.
 
They have trained throughout history 
for a battle their legends foretell will 
decide the fate of the world.
`,r6e=`55
The angel Tyrael has watched over the 
guardians of Arreat throughout 
history. I do not believe that Baal and 
Tyrael have come to fight over a paltry 
few souls.
 
They are here to settle a conflict as old 
as time itself.
`,i6e=`44
During my time with the Horadrim, we 
often debated the nature of Mount 
Arreat.
 
We knew that the Barbarian clans 
zealously guarded the mountain as 
their sacred duty. However, many 
dismissed their zeal as simple 
superstition...combined with an inborn 
hostility toward outsiders.
 
Those Horadrim who trekked up Arreat 
were never heard from again...Still, I 
do not believe they died at the hands of 
Barbarians.
`,n6e=`41
All users of the magical arts know of 
Mount Arreat, but few understand its 
true nature. It is the nexus of an 
unfathomable magic.
 
It bodes ill that the Lord of Destruction 
races to its summit with such purpose. 
I fear for the whole world should Baal 
gain what he seeks.
`,l6e=`59
I have spent decades trying to 
understand the forces at work in this 
world. But in the face of all that is 
transpiring, I realize how meager my 
knowledge is.
 
I will be of assistance where I can, my 
friend.
`,t6e=`54
Though the Elder Council of Harrogath 
is gone, there are many capable young 
leaders to take their place.
 
Anya certainly has enough courage and 
intelligence to lead them all, if they can 
survive this catastrophe.
`,o6e=`53
Ah, Anya. Such a fine example of 
feminine strength...
 
She reminds me of the Zakarum 
priestesses I knew in my youth. They 
don't take vows of chastity, you know.
`,s6e=`65
It is fortunate that this town has such a 
talented smith.
 
The quality of Larzuk's work surely 
complements your skills. In fact, he 
would have been quite welcome 
amongst the Horadrim.
`,c6e=`54
It is my belief that the Soulstones are at 
the center of this conflict. If only that 
fool Marius had not intervened, Baal 
would still be imprisoned within Tal 
Rasha.
`,m6e=`54
You have proven yourself a true hero to 
me and my people.
 
These are dark times, warrior. I hope 
you can bring an end to Baal's reign of 
destruction. 
 
Our Council of Elders is gone -- my 
father, Aust, among them. The one 
thing that keeps us from total despair 
is the promise of vengeance against 
Baal.
`,p6e=`45
Now that the Elders are all dead, I don't 
know who will guide our people through 
this dark time. I was to be next in line 
after my father, but this burden is too 
great for me to shoulder alone. 
 
We are a people of strong blood. I shall 
do what I can and let fate do the rest.
`,d6e=`82
Baal's minions are not to be trifled with. 
In their bloodlust they will sacrifice 
themselves to destroy you.
`,u6e=`60
Many outsiders believe that the 
fantastic stories about our ancestors, 
the Ancients, are but fables. However, I 
believe that the Ancients were more 
than human -- that mankind has fallen 
from what it once was.
`,g6e=`58
When I was a child, the Elders told us 
stories about the mountain and its 
power...and how the Barbarian people 
are bound to it as protectors.
 
Baal is not just taking our land -- with 
every step he takes up the mountain, 
he takes a part of who we are as a 
people.
`,M6e=`72
I am truly glad you are here, warrior. 
Perhaps things would be different now 
if we had asked for assistance from 
the neighboring kingdoms.
 
Our foolish, foolish pride...
`,h6e=`54
My father, Aust, was among those 
Elders wise enough to see that we 
would need outside help to deal with 
Baal's legions. He believed that this 
conflict would affect the entire world, 
not just our homeland. He said that 
Mount Arreat is as necessary to the 
world's survival as food and water is to 
our own.
 
I believe this to be true.
`,v6e=`50
Qual-Kehk's confidence in his abilities 
once bordered on arrogance, but in the 
early days of the siege, he was 
humbled by Baal. While he saved us 
from immediate destruction, a third of 
our warriors were lost.
 
None felt those losses more than he. 
Though he may not admit it, your 
presence gives him hope, warrior.
`,H6e=`78
If Larzuk could sing or dance half as 
well as he smiths, he'd be married by 
now.
 
...Just look at those shoulders.
`,b6e=`57
Nihlathak was the last of our Elders, 
whose charge it was to safeguard the 
mountain. He alone tried to guide us 
through the most desperate time in our 
history -- but he was just as helpless as 
the rest of us.
 
I cannot forgive his betrayal, but I can 
learn from it.
`,A6e=`60
Our people believe that the Ancients 
protecting Mount Arreat have the 
power to stop Baal. Unfortunately, the 
Lord of Destruction has shown great 
power to undermine our faith.
`,x6e=`55
I am Larzuk, the armorer. My ancestors 
were some of the finest craftsmen in 
Harrogath. 
 
Regretfully, my supplies run lower with 
every passing day, yet the demons 
beyond the walls have not weakened. 
 
I fear the time is near when I must put 
down my hammer and take up a sword, 
instead.
`,N6e=`42
So, you're an Amazon. I have heard 
rumors about your kind. Your unusual 
weapons could prove a challenge to my 
skills, but I'm prepared to meet it.
 
I am Larzuk, the armorer. My ancestors 
were some of the finest craftsmen in 
Harrogath. Regretfully, my supplies run 
lower with every passing day, yet the 
demons beyond the walls have not 
weakened. I fear the time is near when 
I must put down my hammer and take 
up a sword, instead.
`,f6e=`65
I've heard that you Amazons excel at 
killing from a distance. From what I've 
seen, that's the best way to deal with 
Hell's minions. 
 
Are all of your kind so...big?
`,k6e=`65
Why did you ever leave your beautiful 
islands to come to this frozen 
battleground? Perhaps if we both 
survive this, we'll travel back there 
together.
`,C6e=`75
Has that infernal howling been keeping 
you awake at night, too? Some think 
it's the howling of animals, but those 
sounds don't come from any beast I've 
ever known.
`,y6e=`69
Demonic forces have been using our 
own towers and barricades against us. 
You know, it would be wise to cut the 
demons down in the open before they 
can mount those fortifications.
`,L6e=`70
Nihlathak's despair is infectious -- and 
his behavior does not befit an Elder of 
his stature. I think we'd be better off 
without him.
`,T6e=`63
I've offered Qual-Kehk my ideas on how 
to break the siege, but he dismisses 
them. Is it because I lack scars of 
battle, or does he think I'm a couple 
arrows short of a quiver?
`,S6e=`64
Legend has it that the top of Mount 
Arreat is guarded by the spirits of our 
ancestors. Though our people are 
forbidden to climb to the mountain's 
summit, some foreign travelers have 
made the attempt.
 
None have ever returned.
`,w6e=`66
This is a lively town during our victory 
celebrations. We Barbarians train long 
and hard from childhood to become 
warriors, and we celebrate with equal 
fervor.
 
You didn't happen to bring along any 
ale to trade?
`,D6e=`54
Every day, one of my friends dies 
fighting outside the town walls, while I 
tend my anvil here unscathed. If only 
we didn't need weapons so badly, I 
could be out doing my share of the 
fighting. 
 
Good luck to you, warrior.
`,P6e=`56
Just so you know...The gold you pay me 
doesn't line my pockets. Much of it 
goes to buy the raw metal I need to 
melt down for weapons and armor. The 
rest -- well, all I can spare -- goes to 
Malah and Qual-Kehk for other 
supplies.
`,I6e=`35
I, Malah, welcome you to Harrogath, 
the last stronghold of Order on Mount 
Arreat. You have come to the right 
place if you intend to defeat Baal the 
Lord of Destruction.
 
Baal has laid waste to our mountain 
and its denizens. His minions continue 
to attack our town, while Qual-Kehk 
and his men have proven helpless to 
stop them. Baal is still out on the 
mountain looking for something -- but I 
know not what. 
 
All of the Elders, save Nihlathak, 
sacrificed themselves to place a 
protective ward around Harrogath.
 
Some of us here, certainly Nihlathak, do 
not appreciate your presence. We are a 
proud people, and it is not easy for us 
to accept aid. I, however, am glad you 
are here.
 
If you need healing or a potion, please 
come to me. See Larzuk for weapons, 
armor, and repairs. Nihlathak, despite 
his disposition, may be of some 
assistance with other wares. Finally, 
Qual-Kehk, our Man-At-Arms, leads 
Harrogath's remaining forces against 
Baal.
`,E6e=`36
A Sorceress...Here in Harrogath?
 
There was a time, child, when I thought 
I was destined to follow your kind's 
path. However, my powers never 
developed beyond the simplest of 
spells. Although I can heal almost any 
wound with time and energy, there is 
little I can do to help against Baal.
 
But enough of that...I spend too much 
time in reflection and have forgotten 
my manners.
 
I, Malah, welcome you to Harrogath, 
the last stronghold of Order on Mount 
Arreat. You have come to the right 
place, if you intend to defeat Baal the 
Lord of Destruction.
 
Baal has laid waste to our mountain 
and its denizens. His minions continue 
to attack our town, while Qual-Kehk 
and his men have proven helpless to 
stop them. Baal is still out on the 
mountain looking for something -- but I 
know not what. 
 
All of the Elders, save Nihlathak, 
sacrificed themselves to place a 
protective ward around Harrogath.
 
Some of us here, certainly Nihlathak, do 
not appreciate your presence. We are a 
proud people, and it is not easy for us 
to accept aid. I, however, am glad you 
are here.
 
If you need healing or a potion, please 
come to me. See Larzuk for weapons, 
armor, and repairs. Nihlathak, despite 
his disposition, may be of some 
assistance with other wares. Finally, 
Qual-Kehk, our Man-At-Arms, leads 
Harrogath's remaining forces against 
Baal.
`,R6e=`34
You have traveled far only to return 
home to us, Barbarian. Ohh...Much has 
happened in Harrogath since you left. 
Our homeland is hardly recognizable 
with so much evil about.
 
Yet, I've managed to survive so far. 
You've seen your share of suffering as 
well, I'm sure. Seeing you again -- alive 
-- does my heart good. I shall pray that 
you can help us out of this hell.
 
Baal has laid waste to our mountain 
and its denizens. His minions continue 
to attack our town, while Qual-Kehk 
and his men have proven helpless to 
stop them. Baal is still out on the 
mountain looking for something -- but I 
know not what.
 
Nihlathak is the last survivor of the 
Council of Elders, but I'm afraid he has 
not been himself lately. The other 
Elders sacrificed themselves to place a 
protective ward around Harrogath. If 
Nihlathak is curt with you, it is because 
he feels responsible for our situation. 
He does not relish sending more of our 
people out to die.
 
So much has changed since you left 
that I see little hope for us in this life.
 
If you need healing or a potion, please 
come to me. See Larzuk for weapons, 
armor, and repairs. Nihlathak, despite 
his disposition, may be of some 
assistance with other wares. Finally, 
Qual-Kehk, our Man-At-Arms, leads 
Harrogath's remaining forces against 
Baal.
`,B6e=`53
I'm aware of the amazing magical 
powers a Sorceress can channel. If we 
survive Baal's wrath, I would be most 
honored if you could demonstrate and 
perhaps teach me something of what 
you know. 
 
I may be old, but I'm not dead.
`,q6e=`42
I know you and my son, Bannuk, did not 
part on the best of terms. He did not 
understand the wanderlust that drove 
you to leave your homeland. However, 
even though Bannuk could never admit 
it to me, as he grew older I could see 
that same desire in his eyes.
 
Oh...It's a pity I didn't encourage him to 
go with you. He might still be alive 
today.
`,G6e=`57
Though once considered shelter by our 
people, the Ice Caves offer no refuge 
from the dark horde. There are 
creatures there that will freeze your 
heart before feasting upon it.
`,U6e=`107
On the battlefield, turning your back on 
even the dead is unwise.
`,O6e=`60
This battle plays mind tricks on our 
warriors. Those fortunate enough to 
have returned from the mountainside 
claim to have seen angels in flight.
 
Fly they might, but that certainly does 
not make them angels.
`,z6e=`53
Perhaps you have heard the accounts 
of my son's horrible death at the hands 
of Baal's minions. He was my last living 
child...
 
The oath of compassion I have taken as 
a healer extends only to humankind.
 
Cut them down, warrior. All of them!
`,F6e=`78
The catapults are infernal machines 
made of demon flesh fused with steel.
 
Be wary of them.
`,W6e=`60
Qual-Kehk is a worthy leader, but the 
losses have borne heavily upon him. He 
is only impatient because he judges the 
worth of a warrior by action, not 
words.
 
You must prove yourself worthy of his 
trust.
`,j6e=`52
Larzuk possesses a good soul, but at 
times his mind seems quite unsound. 
 
He once asked me for twenty of my 
finest sheepskins. He said he would fill 
them with hot air and float like a cloud 
above the battlefield to spy on Baal's 
legions! 
 
I worry the siege has driven him mad.
`,_6e=`90
Be cautious, warrior.
 
Though I am an experienced healer, 
resurrection is beyond my powers.
`,V6e=`53
I pray for the day when the fields are 
covered in snow unstained by the blood 
of our own. Perhaps that day will come 
soon...Perhaps never...
 
Oh...But I forget myself. How may I aid 
your quest?
`,J6e=`64
Your gold is most helpful. Medical 
supplies for our wounded are scarce 
and very expensive.
 
When we can find a supplier, oh, we 
must pay dearly for what we need.
`,Q6e=`44
With the exception of Qual-Kehk, the 
townspeople do not see what I see -- 
the massacre we face.
 
Our bravest, strongest heroes hobble 
back to me begging for help. I do what 
I can -- healing and bandaging some, 
preparing the others for what lies 
beyond.
`,K6e=`43
Well, well. The siege has everything in 
short supply...except fools. 
 
Why would you seek this place, 
stranger? Are you a vulture come to 
loot the bodies of our fallen warriors? 
 
Regardless, this is no place to make a 
name for yourself. The mountain is 
ours to protect. It is only a matter of 
time before Hell's legions are routed.
`,Y6e=`54
Well, well...An Assassin!
 
Heh, heh...While I am sure we are all 
grateful for your presence in our 
troubled town, you need not have made 
the journey.
 
I can personally say that your skills are 
not required here. You would serve 
your clan better elsewhere.
`,X6e=`45
Ahhh, a Necromancer.
 
While I admire your courage in seeking 
out the darker side of magic, we really 
have little need of your skills. The 
battle will turn soon enough without 
your meddling. 
 
Yet, I should have expected to see your 
kind here. You are like a moth to the 
flame -- drawn to all this death. It 
feeds you in more ways than one, does 
it not?
`,$6e=`49
If you're looking for cases of 
treacherous magic, Assassin, take a 
hard look at Larzuk. He was the only 
one in town who escaped the Red Fever 
last spring. He claimed his good 
fortune was due to 'hand washing' 
before meals.
 
Hmmm...Very suspicious...
`,Z6e=`48
Why would you seek this place, 
stranger? Are you a vulture come to 
loot the bodies of our fallen warriors? 
 
Regardless, this is no place to make a 
name for yourself. The mountain is 
ours to protect. It is only a matter of 
time before Hell's legions are routed.
`,eAe=`67
Qual-Kehk is useless. He has blindly 
sent our warriors to their deaths, 
assuming Baal's legions would fight as 
men do. Of course, everyone knows 
they do not.
`,aAe=`57
The demon hordes have grown powerful 
beyond measure, aided by our foolish 
mistakes. But I may have found a way 
to correct those mistakes...
`,rAe=`37
Oh yes...I remember our warriors as 
children. Malah would set their broken 
bones and give them powders for their 
fevers. Now, they return to her with 
wounds that will never heal.
 
I am tired...Please...leave me.
`,iAe=`133
If you have nothing useful for me, be on 
your way!
`,nAe=`81
Anya's father was my good friend. 
There are so many to mourn...I have 
no time for you!
`,lAe=`53
I have long been criticized, but 
especially of late -- since the deaths of 
my fellow Elders. Through it all, I have 
learned one thing. Each man must do 
what's right, no matter what others 
may think.
`,tAe=`65
The Council of Elders always believed 
itself prepared for the coming of the 
Three. Obviously, we were not prepared 
enough.
`,oAe=`45
I am Qual-Kehk, the Senior Man-At-Arms 
of Harrogath.
 
You have the look of a warrior...An 
extra soldier will be useful. But don't 
expect anyone to mourn if you get 
yourself killed. 
 
Baal is true to his namesake. He has 
ravaged through our lands like a 
merciless plague.
 
The protective ward laid down by our 
lost Elders helps hold the evil at bay, 
but Baal's siege has taken its toll all 
the same.
 
Most of my men are now dead. Others 
are trapped in the mountain passes.
 
But I swear we are not beaten yet! We 
will fight to the end to protect this 
mountain!
`,sAe=`42
A Paladin! I have long heard of your 
people.
 
As a young warrior I even considered 
the pilgrimage to Kurast. But I was 
younger then and foolish. My place has 
always been here -- protecting 
Harrogath, and Mount Arreat with it.
 
I am Qual-Kehk, the Senior Man-At-Arms 
of Harrogath.
 
You have the look of a warrior...An 
extra soldier will be useful. But don't 
expect anyone to mourn if you get 
yourself killed. 
 
Baal is true to his namesake. He has 
ravaged through our lands like a 
merciless plague.
 
The protective ward laid down by our 
lost Elders helps hold the evil at bay, 
but Baal's siege has taken its toll all 
the same.
 
Most of my men are now dead. Others 
are trapped in the mountain passes.
 
But I swear we are not beaten yet! We 
will fight to the end to protect this 
mountain!
`,cAe=`42
A Druid in Harrogath! Have things truly 
come to this?
 
After the Mage Wars, I assumed Druids 
would never be seen in Harrogath 
again. You take a big chance coming 
here! 
 
To be honest, I have never been 
comfortable with your shape-shifting 
kind, but I do respect your search for 
balance and peace. So, if you trust us 
enough to enter our gates, I trust you 
enough to let you stay.
 
I am Qual-Kehk, the Senior Man-At-Arms 
of Harrogath.
 
You have the look of a warrior...An 
extra soldier will be useful. But don't 
expect anyone to mourn if you get 
yourself killed. 
 
Baal is true to his namesake. He has 
ravaged through our lands like a 
merciless plague.
 
The protective ward laid down by our 
lost Elders helps hold the evil at bay, 
but Baal's siege has taken its toll all 
the same.
 
Most of my men are now dead. Others 
are trapped in the mountain passes.
 
But I swear we are not beaten yet! We 
will fight to the end to protect this 
mountain!
`,mAe=`67
It would be an honor to have a warrior 
of the Light fighting side-by-side with 
my men.
 
I can see your faith gives you great 
strength, Paladin, but don't expect it to 
keep you out of harm's way.
`,pAe=`61
Harrogath has great need of your 
powers, noble Druid. However, in the 
face of this supernatural onslaught, 
are your natural powers up to the 
task?
`,dAe=`44
The death of Malah's son was a great 
tragedy. He was our finest archer.
 
While leading a successful campaign 
against Baal's forces, he was impaled 
on a demon's spear. The wound was 
such that...Well, even Malah herself 
acknowledges that quick death was a 
blessing.
`,uAe=`57
We have lost many well-trained warriors 
to Baal's siege machines. Their range is 
great. Though, they are vulnerable if 
you close the distance quickly enough.
`,gAe=`96
Baal's legions seem countless, but 
slaying their commanders takes some 
of the fight out of them.
`,MAe=`58
Early on, parties of our best scouts 
were ambushed by demons that 
spawned from the very air around 
them. Survivors often mentioned a 
strange creature floating in the 
distance.
 
Perhaps taking it down could prevent 
some nasty surprises.
`,hAe=`57
This is unlike any battle I have ever 
fought. While we ration food and 
water, the demon hordes feast nightly 
on the flesh and blood of our dead.
`,vAe=`48
Larzuk is a talented blacksmith, but his 
head is full of some strange ideas. 
 
Just the other day he came to me with a 
plan to break the siege. He wanted to 
fill large pipes with exploding powders 
and steel balls, then...Well, like I said, 
strange.
`,HAe=`46
Our Elders were wise leaders in more 
peaceful times, but now the survival of 
our people has fallen to me. My men 
and I will fight to the death, but there's 
no way to ensure the outcome.
 
I used to believe that nothing could 
break through our guard and assault 
the holy mountain. I know now that I 
was horribly mistaken.
`,bAe=`45
If you're here to defeat Baal, you must 
prove it!
 
As we speak, Harrogath is under siege 
by Baal's demons. Catapults rain death 
just outside the town walls.
 
Baal himself travels up the sacred 
mountain, having left in charge here 
one of his most vicious generals, Shenk 
the Overseer. A ruthless taskmaster, 
he lashes his own minions into suicidal 
frenzies on the battlefield.
 
If you wish to prove yourself to us, 
destroy the monster, Shenk, that 
commands those infernal catapults 
outside Harrogath.  If you manage to 
do this, return to me.
`,AAe=`150
Uh...Did I mention there were catapults?
`,xAe=`83
I believe that stopping the siege on 
Harrogath is the only way for you to 
earn the trust of these people.
`,NAe=`84
You've proven your skill at rescuing fair 
maidens...but how are you at killing 
vicious beasts?
`,fAe=`77
Qual-Kehk and his men have been 
fighting to break the siege for some 
time. Where many have failed, you may 
succeed.
`,kAe=`70
After so many have died, who are you 
to think you can accomplish what our 
proud warriors could not?
`,CAe=`66
About to face Shenk the Overseer and 
stop the siege, are you? You should 
ask Malah to perform your last rites 
before you go, stranger.
`,yAe=`90
What's the matter, hero? Questioning 
your fortitude? I know we are.
`,LAe=`105
I understand your reluctance, but now 
is the time to strike.
`,TAe=`66
Those demons have been out there 
since before your arrival. Can you do 
nothing to stop them?
 
Your task is a simple one, warrior. Find 
Shenk and destroy him.
`,SAe=`64
This may not be very encouraging, but 
you have fared better than the others 
who passed through those gates.
 
In regards to Shenk the Overseer, 
remember: a general is nothing without 
his men.
`,wAe=`78
What are you still doing here? I thought 
you were going off to die.
 
Go...Be quick about it.
`,DAe=`93
So, you still live. You're either quick or a 
coward.
`,PAe=`63
You're an even greater warrior than I 
expected...Sorry for underestimating 
you.
 
As a token of my appreciation, I will 
craft sockets into an item of your 
choosing, and from now on, you'll get 
the best price for all my wares.
`,IAe=`60
Those catapults were like nothing I have 
ever seen before. You have prevailed 
against Shenk, my friend, but Baal is 
still far ahead of you.
`,EAe=`108
I was starting to wonder how long it 
would take you to stop those beasts.
 
Good job.
`,RAe=`94
Oh...At last, the siege is ended. You 
truly are an angel.
 
I thank you.
`,BAe=`65
Ending the siege does not earn 
immediate respect, outsider.
 
Respect only comes with sacrifice -- 
something I'm sure you know nothing 
of.
`,qAe=`68
So...You managed to stop the siege.
 
You are more powerful than I gave you 
credit for. You have rightfully earned 
my respect.
`,GAe=`58
My concerns have turned to my men 
taken prisoner on the battlefield by 
Baal's demons. I hate to think what's 
happened to them.
 
As you journey up the mountain, keep 
your eyes open for my soldiers and 
bring them back to me if you can.
`,UAe=`85
Those of my men fortunate enough to 
escape on their own told me that they 
were held captive in the highlands and 
plateaus.
`,OAe=`74
I know firsthand that captivity is a sad 
fate for a man. Find them quickly.
`,zAe=`85
If those men are being treated like I 
was, you must find them. They won't 
survive much longer.
`,FAe=`73
I crafted the swords and armor for 
Qual-Kehk's men. They were like 
brothers to me. I can't imagine the pain 
they must be suffering.
 
Save them if you can!
`,WAe=`84
Qual-Kehk's men have been imprisoned 
for some time. They are certain to be 
tired and weak.
 
You must protect them once you free 
them.
`,jAe=`94
You have proven you can take life, 
warrior, but can you save it as well?
`,_Ae=`95
They say that discretion, not 
procrastination, is the better part of 
valor.
`,VAe=`78
More of my men are still alive out there. 
I am certain of it!
 
Find them. Free them from their cages 
and bring them back to me.
`,JAe=`63
If you are having trouble finding 
Qual-Kehk's soldiers, you should talk to 
Malah. She healed those who made it 
back before. Perhaps she would have 
some advice.
`,QAe=`115
Well, you found me on the mountain; I'm 
sure you'll find them too.
`,KAe=`76
As a kid, I used to play soldier among 
the barricades on the mountain. 
There's no easy way through that maze 
of walls.
`,YAe=`67
Soldiers who made it back told of a 
system of barricades placed among the 
mountain passes. They said that is 
where the prisoners are held.
`,XAe=`52
Did you ever stop to think why these 
demons are capturing Qual-Kehk's 
men? Why they are attacking us? Have 
you considered what Baal wants with 
the mountain?
 
No. You've not. You have no idea what 
you are dealing with.
`,$Ae=`51
Thank you for rescuing my men. They 
have spoken well of your bravery in 
battle. Perhaps there is hope for us 
after all. 
 
If you wish, you may hire some of my 
mercenaries that you saved. And 
please...take this set of runes. I had 
been saving them for a socketed shield, 
but I think you'll make better use of 
them.
 
Be sure to set them in the right order 
for their fullest effect.
`,ZAe=`80
You've become a hero to this town, my 
friend. The shadows have lifted ever 
since you brought the Light to 
Harrogath.
`,exe=`107
I'm sure those men appreciate the 
freedom you gave them...as much as I 
do.
`,axe=`55
Since your arrival, Cain has spoken of 
your deeds in the Southern Kingdoms, 
defeating both Mephisto and Diablo. At 
first, I scoffed at his tales, but I'm 
finding them more believable with every 
passing day.
`,rxe=`73
You have inspired the people in this 
town -- not only those you rescued, but 
those you've helped in other ways as 
well.
`,ixe=`72
So. You brought the lost sheep home to 
the shepherd. Well done.
`,nxe=`43
There is a matter which I hesitate to 
share, but I believe you are the only 
one who can help me now.
 
Anya, the young alchemist and 
daughter to one of our slain Elders, 
has been missing for some time. She is 
a strong, crafty woman with a spirit 
like no other.
 
One night, just before your arrival, I 
overheard her and Nihlathak arguing 
about her father's death. The next 
morning she was gone.
 
Nihlathak has his own tale as to where 
she went and why. Don't believe him! I 
fear he is at the root of her 
disappearance.
 
Please, if you can, search for Anya and 
bring her back to us. She'll know what 
to do about Nihlathak.
`,lxe=`94
When you talk to Nihlathak, be careful. 
There is no telling what he will say or 
do.
`,txe=`59
I would listen to Malah. Nihlathak 
speaks with a venomous tongue and 
acts as if the entire weight of this town 
rests upon his shoulders.
 
Perhaps there is more going on here 
than we know.
`,oxe=`57
Anya is an amazing alchemist, 
especially for her young age. As long 
as I've known her, she's never let 
anything stop her from pursuing what 
she believed in. 
 
I wouldn't doubt that Nihlathak is 
involved. Ever since her father died, 
they haven't gotten along.
`,sxe=`41
Anya! Who have you been talking to? 
Likely it was that meddling Malah. 
 
Well, I'll tell you what really happened. 
Anya came to me for guidance, after 
receiving a vision that her mother and 
younger brother were trapped in the 
lands beyond the Ice Caves. She had 
decided to go rescue them. 
 
I told her that her quest was a foolish 
one and that she would be safer 
staying within the city walls. However, 
she is a willful girl and would not listen 
to me. 
 
The next morning, she was gone. No 
one is more distraught than I over 
losing her. 
 
However, if you feel the need to be 
Malah's errand child, I won't try to stop 
you.
`,cxe=`43
Anya's father, Aust, was our wisest 
Elder. He was killed along with the 
other Elders who erected the ward that 
protects this city. The ward has kept 
Baal's demons out of Harrogath, but at 
a costly sacrifice. 
 
Nihlathak, on the other hand, was the 
only Elder to escape the demons. 
Somehow, he alone managed to find 
sanctuary, while the others died 
around him.
 
Ever since that day, Nihlathak and Anya 
have been at odds.
`,mxe=`52
If it were anyone else, I would assume 
her dead. However, Anya is not so 
easily beaten. I know she must be alive.
`,pxe=`60
Nihlathak's story does sound 
reasonable, considering what I've 
heard about Anya. However, the best 
lies are often hidden within truth.
`,dxe=`56
As the daughter of Elder Aust, Anya is 
the only person, besides Nihlathak, 
who has any real knowledge of Mount 
Arreat's secrets. I'd hate to see our 
fate in the hands of Nihlathak alone.
`,uxe=`46
Look, I've told you! She's dead! If you 
knew what was good for you, you'd 
concentrate your efforts on saving 
Harrogath -- not on lost causes like 
Anya.
`,gxe=`81
It seems like everyone feels Nihlathak 
played a part in Anya's disappearance.
 
Why would he do such a thing?
`,Mxe=`56
So! That snake Nihlathak was behind 
Anya's disappearance...and he trapped 
her with a freezing curse.
 
Here. Take this potion to Anya and give 
it to her. That should release her.
`,hxe=`54
Goodness! Anya frozen by that fallen 
Barbarian, Nihlathak...Perhaps Malah 
can help you where I cannot.
`,vxe=`80
Poor Anya! I should've known Nihlathak 
was a traitor...
 
If you find him alive, kill him for me!
`,Hxe=`70
The snake has slipped our grasp! While 
you were gone, Nihlathak disappeared.
 
I'll bet Anya knows how to track him 
down.
`,bxe=`50
Hero. Nihlathak did this to me!
 
If you've come to help me, my only hope 
lies with Malah.
 
Please...Tell her you've found me...
`,Axe=`48
Thank you so much for bringing Anya 
back to us. I have devised this spell to 
increase your resistances as a token of 
my thanks. I know it isn't much, but I 
hope you find it helpful.
 
Please go talk to Anya. She has urgent 
news concerning Nihlathak.
`,xxe=`62
For one so young, Anya commands 
great respect. Now that she is here, I 
will make it a point to talk to her about 
Mount Arreat.
 
You should do the same.
`,Nxe=`67
I never liked Nihlathak, but I never 
suspected that he'd betray us! I just 
can't understand how an Elder could do 
such a thing.
`,fxe=`140
Your rescue of Anya was quite an 
accomplishment.
`,kxe=`80
Thank you, hero, for rescuing me.
 
To show my personal gratitude, I give 
you this. I had it custom-made for you 
by Larzuk.
`,Cxe=`43
Nihlathak told me he struck a deal with 
Baal to protect Harrogath. In exchange 
for the demon's mercy, the misguided 
fool plans to give Baal the Relic of the 
Ancients, our most holy totem!
 
Doing so will allow Baal to enter Mount 
Arreat unchallenged by the Ancients. I 
tried to stop Nihlathak, but he 
imprisoned me in that icy tomb.
 
Nihlathak must be stopped before he 
dooms the whole world. As much as I 
would love to strangle the life out of 
him, I'm afraid I haven't the strength.
 
You must go to his lair through this 
portal I've opened, kill him, and then 
bring back the Relic of the Ancients.
 
Stop Nihlathak from destroying what we 
have striven for eons to protect.
`,yxe=`90
As noble as Nihlathak's intentions are, 
nothing can excuse his actions.
`,Lxe=`50
Regretfully, I know very little about this 
Relic. However, if what the others say 
is true, then Baal must not gain 
possession of it.
 
Stop Nihlathak...before all is lost.
`,Txe=`65
My worst fear has come true. Nihlathak 
has gone mad.
 
You must stop him, before he gives the 
Relic to the Lord of Destruction!
`,Sxe=`56
Now, rescuing Anya -- that's good. 
Talking to me while Nihlathak hands 
over the Relic to Baal -- uh...that's bad!
`,wxe=`60
I saw Nihlathak leave town just before 
you found Anya. He must be held 
accountable for his criminal deeds.
 
Find him and bring him back, if you can. 
Likely, he won't come willingly, and 
you'll be forced to kill him.
 
So be it.
`,Dxe=`55
Nihlathak is a traitor! If Baal gets the 
Relic, he shall enter the mountain and 
wreak havoc there!
 
I cannot believe that Nihlathak would 
give the Relic to Baal in any kind of 
trade. He's truly insane if he believes 
that he can deal with the Lord of 
Destruction.
`,Pxe=`58
Ohh...This is a truly horrible turn of 
events.
 
I know it seems you have always been 
one step behind, my friend. But look at 
it this way...You have evil on the run.
`,Ixe=`160
...What's there to talk about?
 
Kill Nihlathak!
`,Exe=`63
Nihlathak was never the kindest man. 
But for him to betray the whole world...
 
Ahh...Where shall his soul finally rest?
`,Rxe=`65
My advice is to go in quick and hit hard. 
Nihlathak can't be half as tough as the 
beasts you've faced out there.
`,Bxe=`55
You have stopped Nihlathak, but he 
didn't have the Relic! He must have 
already given it to Baal. Now, Baal will 
not be tested when he reaches Arreat's 
summit.
 
...Damn Nihlathak!
 
I do thank you for trying, though. 
Please, allow me to honor your courage 
by magically inscribing your name onto 
an item of your choosing. It's the least 
I can do.
`,qxe=`90
Beware! Baal grows stronger with every 
passing moment.
`,Gxe=`93
Hmmm...What does Baal plan to do 
inside Mount Arreat?
`,Uxe=`65
So, the Relic is lost. Do not dwell on 
failures past. It is your future that 
matters more.
`,Oxe=`57
Nihlathak was a vile demon that shall 
find his home among the tortured 
minions of Hell!
 
You battled the Darkness without fear. I 
laud your skill and courage.
`,zxe=`37
Every time I hear of you, warrior, your 
deeds become more legendary.
 
But take heed. You are approaching the 
very summit of Mount Arreat. I have 
never dared venture there. It is sacred 
-- our most holy place. The legends say 
it is guarded by the Ancient Ones, who 
block the path of all who are unworthy.
 
Your reputation here does not 
matter...It will be the Ancients who 
determine your worthiness.
 
Good luck.
`,Fxe=`63
The Ancients are not our enemies. 
Remember that! They are our 
ancestors -- our gods.
`,Wxe=`90
A test of mettle is a fitting rite of 
passage for a Barbarian hero.
`,jxe=`72
You wouldn't have to test yourself 
against the Ancients if it weren't for 
Nihlathak's treachery. He was a fool 
and deserves to suffer for eternity.
`,_xe=`75
Every night, I've prayed to the Ancients 
to bring us peace...and now you must 
fight them.
 
Huh...Who shall I pray to now, warrior?
`,Vxe=`65
By reaching the summit, you cease 
being just a simple warrior. When you 
come back, you will be far more.
`,Jxe=`114
I warned you!
 
The Ancients are not like the demons 
you're accustomed to fighting.
`,Qxe=`52
We have come too far to be defeated 
now, my friend. I have seen you 
complete many difficult quests. Though 
this may be your greatest trial, it is not 
beyond your reach.
`,Kxe=`71
Look. I must apologize.
 
I feel responsible for your current 
struggle. If I had only stopped 
Nihlathak from giving Baal the Relic, 
you would not have to fight those 
ghosts.
`,Yxe=`70
You've walked on the burial grounds of 
our greatest ancestors. I'm not sure 
whether I should bow before you or 
revile you for committing sacrilege.
 
Tread lightly when you walk with gods.
`,Xxe=`68
Do not doubt yourself. I believe you are 
worthy to pass through the Ancients' 
gates, but you must believe, as well.
`,$xe=`75
Besting the Ancients in battle is a 
mighty feat indeed. I hope this means 
you're ready to battle Baal.
`,Zxe=`67
You have proven yourself to these 
people. They look to you as their 
warrior, their champion.
`,e7e=`82
You stand before me a worthy hero -- 
and on you rests the last hope of our 
people.
 
Bear it well, warrior.
`,a7e=`82
The Ancients have honored you, and in 
turn, so do we. I have no remaining 
doubts about you, now.
`,r7e=`60
I knew the Ancients would find you 
worthy of Mount Arreat's secrets. Now, 
stop Baal before he destroys all that is 
sacred.
`,i7e=`31
You are a worthy hero! We augment 
your skill and grant you entry to the 
interior of Mount Arreat, wherein lies 
the Worldstone.
 
Beware. You will not be alone. Baal the 
Lord of Destruction is already inside. 
 
The Archangel Tyrael has always been 
our benefactor, but even he cannot 
help us now. For Baal blocks Tyrael's 
spiritual presence from entering the 
chamber of the Worldstone. Only you, 
mortal, have the power to defeat Baal 
now.
 
Baal threatens the Worldstone -- and 
through it, the mortal realm, itself. You 
must stop him before he gains full 
control of the sacred stone. With it 
under his control, Baal could shatter 
the boundaries between this world and 
the Burning Hells, thus allowing the 
hordes of the Prime Evils to pour forth 
into the mortal realm like an 
unstoppable tide!
 
If you are weak, the world as you know 
it could be lost forever. You must NOT 
fail!
`,n7e=`51
Remember this. Baal once possessed Tal 
Rasha, one of the most powerful of the 
ancient Horadrim.
 
Your battles with Mephisto and Diablo 
will pale in comparison to your battle 
with Baal.
 
The Lord of Destruction aided by Tal 
Rasha's knowledge...The mountain 
itself will tremble when you clash.
`,l7e=`59
I may be just an armorer, but I know 
this...Baal plans to destroy the world 
with the secrets contained in that 
mountain. It doesn't take a genius to 
know he has to be stopped.
`,t7e=`70
You knew it would eventually come down 
to this. Kill Baal! Finish the game!
`,o7e=`60
Baal has blocked Tyrael from entering 
the Worldstone Chamber? This truly 
has become a battle against Hell.
 
Whether or not it was the Heavens' 
decree, this is your fight now -- your 
destiny.
`,s7e=`63
You have ventured to a place beyond 
legend. You rush to face an evil few 
can even imagine.
 
Be careful, my friend, and may the Light 
watch over you.
`,c7e=`40
I am impressed, mortal. You have 
overcome the greatest challenge this 
world has ever faced and defeated the 
last of the Prime Evils. However, we are 
too late to save the Worldstone. Baal's 
destructive touch has corrupted it 
completely.
 
Given enough time, the Worldstone's 
energies will drain away and the 
barriers between the worlds will 
shatter -- the powers of Hell will flood 
into this...Sanctuary...and eradicate 
your people and everything you've 
labored to build.
 
Therefore, I must destroy the corrupted 
Worldstone before the powers of Hell 
take root. This act will change your 
world forever -- with consequences 
even I cannot foresee. However, it is 
the only way to ensure mankind's 
survival.
 
Go now, mortal. I have opened a portal 
that will lead you to safety.
 
May the Eternal Light shine upon you 
and your descendants for what you've 
done this day. The continued survival 
of mankind is your legacy! Above all 
else, you have earned a rest from this 
endless battle.
`,m7e=`53
You have done the impossible, hero. 
Your defeat of the last of the three 
Prime Evils is a great victory for the 
Light. 
 
Strange that you say that the 
Worldstone must be destroyed. The 
prophecies said nothing about that.
 
Perhaps all we have fought for will be 
lost...or perhaps we'll never need fight 
again!
`,p7e=`40
I knew in time you would defeat Baal. 
You have done everything you set out 
to do, my friend.
 
Ever since you rescued me from 
Tristram, I have believed in you. It has 
been a supreme honor to aid you along 
the way. 
 
So...The Worldstone was corrupted by 
Baal. And now Tyrael must destroy it. 
Worry not. Through whatever lies 
ahead I have faith that the Light will 
guide us both.
 
Go, now, back to the Worldstone 
chamber, and enter the portal Tyrael 
has opened for you.
`,d7e=`74
The Ancients themselves will envy our 
songs about you.
 
Please, don't forget about us! Farewell, 
my friend.
`,u7e=`48
If Tyrael says the Worldstone must be 
destroyed, then it must. We cannot let 
Baal's corruption prevail!
 
The world will change, true -- but who is 
to say it isn't for the better?
`,g7e=`60
The destruction of the Worldstone does 
not bode well for our world. But I'll try 
not to worry...
 
After all, we have warriors like you 
fighting for us and for the Light.
 
Farewell!
`,M7e="Katar",h7e="Wrist Blade",v7e="Cestus",H7e="Claws",b7e="Blade Talons",A7e="Scissors Katar",x7e="Stag Bow",N7e="Reflex Bow",f7e="Maiden Spear",k7e="Maiden Pike",C7e="Maiden Javelin",y7e="Glowing Orb",L7e="Crystalline Globe",T7e="Cloudy Sphere",S7e="Sparkling Ball",w7e="Swirling Crystal",D7e="Ashwood Bow",P7e="Ceremonial Bow",I7e="Ceremonial Spear",E7e="Ceremonial Pike",R7e="Ceremonial Javelin",B7e="Heavenly Stone",q7e="Eldritch Orb",G7e="Demon Heart",U7e="Vortex Orb",O7e="Dimensional Shard",z7e="Matriarchal Bow",F7e="Grand Matron Bow",W7e="Matriarchal Spear",j7e="Matriarchal Pike",_7e="Matriarchal Javelin",V7e="Jawbone Cap",J7e="Fanged Helm",Q7e="Horned Helm",K7e="Assault Helmet",Y7e="Avenger Guard",X7e="Targe",$7e="Rondache",Z7e="Heraldic Shield",eNe="Aerin Shield",aNe="Crown Shield",rNe="Circlet",iNe="Coronet",nNe="Tiara",lNe="Diadem",tNe="Shako",oNe="Hydraskull",sNe="Armet",cNe="Giant Conch",mNe="Spired Helm",pNe="Corona",dNe="Demonhead",uNe="Dusk Shroud",gNe="Wyrmhide",MNe="Scarab Husk",hNe="Wire Fleece",vNe="Diamond Mail",HNe="Loricated Mail",bNe="Boneweave",ANe="Great Hauberk",xNe="Balrog Skin",NNe="Hellforge Plate",fNe="Kraken Shell",kNe="Lacquered Plate",CNe="Shadow Plate",yNe="Sacred Armor",LNe="Archon Plate",TNe="Heater",SNe="Luna",wNe="Hyperion",DNe="Monarch",PNe="Aegis",INe="Ward",ENe="Bramble Mitts",RNe="Vampirebone Gloves",BNe="Vambraces",qNe="Crusader Gauntlets",GNe="Ogre Gauntlets",UNe="Wyrmhide Boots",ONe="Scarabshell Boots",zNe="Boneweave Boots",FNe="Mirrored Boots",WNe="Myrmidon Greaves",jNe="Spiderweb Sash",_Ne="Vampirefang Belt",VNe="Mithril Coil",JNe="Troll Belt",QNe="Colossus Girdle",KNe="Bone Visage",YNe="Troll Nest",XNe="Blade Barrier",$Ne="Sacred Feathers",ZNe="Griffon Headdress",e8e="Hunter's Guise",a8e="Alpha Helm",r8e="Totemic Mask",i8e="Jawbone Visor",n8e="Lion Helm",l8e="Rage Mask",t8e="Savage Helmet",o8e="Slayer Guard",s8e="Akaran Targe",c8e="Akaran Rondache",m8e="Protector Shield",p8e="Gilded Shield",d8e="Royal Shield",u8e="Mummified Trophy",g8e="Fetish Trophy",M8e="Sexton Trophy",h8e="Cantor Trophy",v8e="Hierophant Trophy",H8e="Sky Spirit",b8e="Sun Spirit",A8e="Earth Spirit",x8e="Blood Spirit",N8e="Dream Spirit",f8e="Carnage Helm",k8e="Fury Visor",C8e="Destroyer Helm",y8e="Conqueror Crown",L8e="Guardian Crown",T8e="Sacred Targe",S8e="Sacred Rondache",w8e="Zakarum Shield",D8e="Vortex Shield",P8e="Minion Skull",I8e="Hellspawn Skull",E8e="Overseer Skull",R8e="Succubus Skull",B8e="Bloodlord Skull",q8e="Jewel",G8e="Small Charm",U8e="Large Charm",O8e="Grand Charm",z8e="Keep in Inventory to Gain Bonus",F8e=`Keep it to thaw Anya
Malah's Potion`,W8e="Zod Rune",j8e="Cham Rune",_8e="Jah Rune",V8e="Ber Rune",J8e="Sur Rune",Q8e="Lo Rune",K8e="Ohm Rune",Y8e="Vex Rune",X8e="Gul Rune",$8e="Ist Rune",Z8e="Mal Rune",efe="Um Rune",afe="Pul Rune",rfe="Lem Rune",ife="Fal Rune",nfe="Ko Rune",lfe="Lum Rune",tfe="Io Rune",ofe="Hel Rune",sfe="Dol Rune",cfe="Shael Rune",mfe="Sol Rune",pfe="Amn Rune",dfe="Thul Rune",ufe="Ort Rune",gfe="Ral Rune",Mfe="Tal Rune",hfe="Ith Rune",vfe="Eth Rune",Hfe="Nef Rune",bfe="Tir Rune",Afe="Eld Rune",xfe="El Rune",Nfe="Zod",ffe="Cham",kfe="Jah",Cfe="Ber",yfe="Sur",Lfe="Lo",Tfe="Ohm",Sfe="Vex",wfe="Gul",Dfe="Ist",Pfe="Mal",Ife="Um",Efe="Pul",Rfe="Lem",Bfe="Fal",qfe="Ko",Gfe="Lum",Ufe="Io",Ofe="Hel",zfe="Dol",Ffe="Shael",Wfe="Sol",jfe="Amn",_fe="Thul",Vfe="Ort",Jfe="Ral",Qfe="Tal",Kfe="Ith",Yfe="Eth",Xfe="Nef",$fe="Tir",Zfe="Eld",eke="El",ake="'",rke="Ancients' Pledge",ike="Armageddon",nke="Authority",lke="Beast",tke="Beauty",oke="Black",ske="Blood",cke="Bone",mke="Bramble",pke="Brand",dke="Breath of the Dying",uke="Broken Promise",gke="Call to Arms",Mke="Chains of Honor",hke="Chance",vke="Chaos",Hke="Crescent Moon",bke="Darkness",Ake="Daylight",xke="Death",Nke="Deception",fke="Delirium",kke="Desire",Cke="Despair",yke="Destruction",Lke="Doom",Tke="Dragon",Ske="Dread",wke="Dream",Dke="Duress",Pke="Edge",Ike="Elation",Eke="Enigma",Rke="Enlightenment",Bke="Envy",qke="Eternity",Gke="Exile",Uke="Faith",Oke="Famine",zke="Flame",Fke="Fortitude",Wke="Fortune",jke="Friendship",_ke="Fury",Vke="Gloom",Jke="Glory",Qke="Grief",Kke="Hand of Justice",Yke="Harmony",Xke="Hatred",$ke="Heart of the Oak",Zke="Heaven's Will",eCe="Holy Tears",aCe="Holy Thunder",rCe="Honor",iCe="Revenge",nCe="Humility",lCe="Hunger",tCe="Ice",oCe="Infinity",sCe="Innocence",cCe="Insight",mCe="Jealousy",pCe="Judgement",dCe="King's Grace",uCe="Kingslayer",gCe="Knight's Vigil",MCe="Knowledge",hCe="Last Wish",vCe="Law",HCe="Lawbringer",bCe="Leaf",ACe="Lightning",xCe="Lionheart",NCe="Lore",fCe="Love",kCe="Loyalty",CCe="Lust",yCe="Madness",LCe="Malice",TCe="Melody",SCe="Memory",wCe="Mist",DCe="Morning",PCe="Mystery",ICe="Myth",ECe="Nadir",RCe="Nature's Kingdom",BCe="Night",qCe="Oath",GCe="Obedience",UCe="Oblivion",OCe="Obsession",zCe="Passion",FCe="Patience",WCe="Patter",jCe="Peace",_Ce="Voice of Reason",VCe="Penitence",JCe="Peril",QCe="Pestilence",KCe="Phoenix",YCe="Piety",XCe="Pillar of Faith",$Ce="Plague",ZCe="Praise",eye="Prayer",aye="Pride",rye="Principle",iye="Prowess in Battle",nye="Prudence",lye="Punishment",tye="Purity",oye="Question",sye="Radiance",cye="Rain",mye="Reason",pye="Red",dye="Rhyme",uye="Rift",gye="Sanctuary",Mye="Serendipity",hye="Shadow",vye="Shadow of Doubt",Hye="Silence",bye="Siren's Song",Aye="Smoke",xye="Sorrow",Nye="Spirit",fye="Splendor",kye="Starlight",Cye="Stealth",yye="Steel",Lye="Still Water",Tye="Sting",Sye="Stone",wye="Storm",Dye="Strength",Pye="Tempest",Iye="Temptation",Eye="Terror",Rye="Thirst",Bye="Thought",qye="Thunder",Gye="Time",Uye="Tradition",Oye="Treachery",zye="Trust",Fye="Truth",Wye="Unbending Will",jye="Valor",_ye="Vengeance",Vye="Venom",Jye="Victory",Qye="Voice",Kye="Void",Yye="War",Xye="Water",$ye="Wealth",Zye="Whisper",eLe="White",aLe="Wind",rLe="Wings of Hope",iLe="Wisdom",nLe="Woe",lLe="Wonder",tLe="Wrath",oLe="Youth",sLe="Zephyr",cLe="Spleen",mLe="Scalp",pLe="Soul",dLe="Quill",uLe="Fang",gLe="Flag",MLe="Tail",hLe="Horn",vLe="Eye",HLe="Jawbone",bLe="Brain",ALe="Heart",xLe="Stout",NLe="Antimagic",fLe="Null",kLe="Godly",CLe="Ivory",yLe="Eburine",LLe="Blanched",TLe="Stalwart",SLe="Burly",wLe="Dense",DLe="Thin",PLe="Compact",ILe="Pestilent",ELe="Toxic",RLe="Corrosive",BLe="Foul",qLe="Septic",GLe="Shocking",ULe="Arcing",OLe="Buzzing",zLe="Static",FLe="Condensing",WLe="Flaming",jLe="Smoking",_Le="Smoldering",VLe="Fiery",JLe="Hibernal",QLe="Boreal",KLe="Shivering",YLe="Snowy",XLe="Mnemonic",$Le="Visionary",ZLe="Eagleeye",eTe="Hawkeye",aTe="Falconeye",rTe="Sparroweye",iTe="Robineye",nTe="Paradox",lTe="Howling",tTe="Yelling",oTe="Calling",sTe="Alarming",cTe="Fool's",mTe="Faithful",pTe="Righteous",dTe="Honorable",uTe="Enlightened",gTe="Psychic",MTe="Cunning",hTe="Entrapping",vTe="Communal",HTe="Feral",bTe="Spiritual",ATe="Furious",xTe="Raging",NTe="Echoing",fTe="Resonant",kTe="Sounding",CTe="Mojo",yTe="Venomous",LTe="Noxious",TTe="Fungal",STe="Cursing",wTe="Blighting",DTe="Hexing",PTe="Glacial",ITe="Freezing",ETe="Chilling",RTe="Powered",BTe="Charged",qTe="Sparking",GTe="Volcanic",UTe="Blazing",OTe="Burning",zTe="Diamond",FTe="Celestial",WTe="Elysian",jTe="Astral",_Te="Unearthly",VTe="Arcadian",JTe="Aureolic",QTe="Victorious",KTe="Ambergris",YTe="Camphor",XTe="Chromatic",$Te="Scintillating",ZTe="Turquoise",e9e="Jacinth",a9e="Zircon",r9e="Felicitous",i9e="Lucky",n9e="Wailing",l9e="Screaming",t9e="Argent",o9e="Tin",s9e="Nickel",c9e="Maroon",m9e="Chestnut",p9e="Vigorous",d9e="Brown",u9e="Dun",g9e="Realgar",M9e="Rusty",h9e="Cinnabar",v9e="Vermilion",H9e="Carmine",b9e="Carbuncle",A9e="Serrated",x9e="Scarlet",N9e="Bloody",f9e="Sanguinary",k9e="Pearl",C9e="Divine",y9e="Hallowed",L9e="Sacred",T9e="Pure",S9e="Consecrated",w9e="Lunar",D9e="Frantic",P9e="Hellacious",I9e="Quixotic",E9e="Smiting",R9e="Stellar",B9e="Stinging",q9e="Singing",G9e="Timeless",U9e="Original",O9e="Corporal",z9e="Lawful",F9e="Chaotic",W9e="Fierce",j9e="Ferocious",_9e="Perpetual",V9e="Everlasting",J9e="Laden",Q9e="Pernicious",K9e="Harmful",Y9e="Evil",X9e="Insidious",$9e="Malicious",Z9e="Spiteful",eSe="Precocious",aSe="Majestic",rSe="Sanguine",iSe="Monumental",nSe="Irresistible",lSe="Festering",tSe="Musty",oSe="Dusty",sSe="Decaying",cSe="Rotting",mSe="Infectious",pSe="Foggy",dSe="Cloudy",uSe="Hazy",gSe="Punishing",MSe="Obsidian",hSe="Royal",vSe="Frigid",HSe="Moldy",bSe="Gaudy",ASe="Impeccable",xSe="Soulless",NSe="Heated",fSe="Lasting",kSe="Scorched",CSe="Marred",ySe="Lilac",LSe="Rose",TSe="Shimmering",SSe="Wicked",wSe="Strange",DSe="Repulsive",PSe="Reclusive",ISe="Rude",ESe="Hermetic",RSe="Rainbow",BSe="Colorful",qSe="Odiferous",GSe="Grinding",USe="to Druid Skills",OSe="to Assassin Skills",zSe=" Sockets",FSe=" to Attack Rating vs. Demons",WSe=" to Attack Rating vs. Undead",jSe=" to Damage vs. Demons",_Se=" percent to Attack Rating",VSe=" to Javelin and Spear Skills",JSe=" to Passive and Magic Skills",QSe=" to Bow and Crossbow Skills",KSe=" to Defensive Aura Skills",YSe=" to Offensive Aura Skills",XSe=" to Combat Skills",$Se=" to Summoning Skills",ZSe=" to Poison and Bone Skills",ewe=" to Curses",awe=" to Warcry Skills",rwe=" to Combat Skills",iwe=" to Masteries Skills",nwe=" to Cold Skills",lwe=" to Lightning Skills",twe=" to Fire Skills",owe=" to Summoning Skills",swe=" to Shape-Shifting Skills",cwe=" to Elemental Skills",mwe=" to Trap Skills",pwe=" to Shadow Discipline Skills",dwe=" to Martial Art Skills",uwe="(Based on Character Level)",gwe="(Increases During Nighttime)",Mwe="(Increases During Daytime)",hwe="(Increases Near Dawn)",vwe="(Increases Near Dusk)",Hwe=" Charges of",bwe="Increased Stack Size",Awe="Indestructible",xwe="Repairs %d durability per second",Nwe="Repairs %d durability in %d seconds",fwe="Replenishes quantity",kwe="Cast a Level %d",Cwe="When You Swing",ywe="When You Get Hit",Lwe="When You Hit an Enemy",Twe="Charges",Swe="Level",wwe="Per Level",Dwe="(%d/%d Charges)",Pwe="(",Iwe=")",Ewe="Stealth",Rwe="Immunity to Poison",Bwe="Cursed",qwe="Per Player in Party",Gwe="Orb Class",Uwe=" Elemental Damage",Owe="Helms:",zwe="Shields:",Fwe="Weapons:",Wwe="Armor:",jwe="Adds to Strength",_we="Adds to Defense Rating",Vwe="Adds to Attack Rating",Jwe="Adds to Maximum Mana",Qwe="Adds Resistance to Cold",Kwe="Adds Cold Damage to Attack",Ywe="Adds to Dexterity",Xwe="Adds Resistance to Poison",$we="Adds Poison Damage to Attack",Zwe="Adds to Maximum Life",eDe="Adds Resistance to Fire",aDe="Adds Fire Damage to Attack",rDe="Adds to Attack Rating",iDe="Adds to All Resistances",nDe="Adds to Damage vs. Undead",lDe="Adds to Chance to Find Magic Items",tDe="Adds Resistance to Lightning",oDe="Adds Lightning Damage to Attack",sDe="Adds Mana and Life Regeneration",cDe="Adds Attacker Takes Damage",mDe="Adds Mana and Life Steal to Attack",pDe="Coldkill",dDe="Islestrike",uDe="Spellsteel",gDe="Stormrider",MDe="Fleshrender",hDe="Moonfall",vDe="Earthshaker",HDe="Bloodletter",bDe="Hexfire",ADe="Riftslash",xDe="Headstriker",NDe="Cloudcrack",fDe="Swordguard",kDe="Spineripper",CDe="Stormspike",yDe="Ribcracker",LDe="Warpspear",TDe="Skull Collector",SDe="Skystrike",wDe="Endlesshail",DDe="Vampire Gaze",PDe="Gore Rider",IDe="Lava Gout",EDe="Visceratuant",RDe="Shaftstop",BDe="Blackhorn",qDe="Magewrath",GDe="Cliffkiller",UDe="Riphook",ODe="Razorswitch",zDe="Meatscrape",FDe="Deathbit",WDe="Warshrike",jDe="Gut Siphon",_De="Razor's Edge",VDe="Stone Rattle",JDe="Marrow Grinder",QDe="Demon Limb",KDe="Steel Shade",YDe="Fleshbone",XDe="Odium",$De="Bonehew",ZDe="Steelrend",ePe="Shadow Dancer",aPe="Soul Drainer",rPe="Rune Master",iPe="Death Cleaver",nPe="Leviathan",lPe="Dawn Bringer",tPe="Dragontooth",oPe="Wisp Projector",sPe="Lacerator",cPe="Viperfork",mPe="Spirit Keeper",pPe="Hellrack",dPe="Rockhew",uPe="Catgut",gPe="Ghostflame",MPe="Shadow Killer",hPe="Eaglewind",vPe="Windhammer",HPe="Thunderstroke",bPe="Giant Maimer",APe="Bloodmoon",xPe="Djinn Slayer",NPe="Cranebeak",fPe="Warhound",kPe="Gulletwound",CPe="Darksoul",yPe="Earth Shifter",LPe="Fleshripper",TPe="Stonerage",SPe="Jade Talon",wPe="Wraithfang",DPe="Blade Master",PPe="Cerebus' Bite",IPe="Sinblade",EPe="Rune Slayer",RPe="Excalibur",BPe="Stoneraven",qPe="Moonrend",GPe="Nightsummon",UPe="Bonescalpel",OPe="Snake Tongue",zPe="Lifechoke",FPe="Carnage Leaver",WPe="Ghost Leach",jPe="Soul Reaper",_Pe="Stormwillow",VPe="Moon Shadow",JPe="Strong Oak",QPe="Demonweb",KPe="Shade Falcon",YPe="Glimmershred",XPe="Wraith Flight",$Pe="Windstrike",ZPe="Titan's Fist",eIe="Hadeshorn",aIe="Rockstopper",rIe="Stealskull",iIe="Iron Pelt",nIe="Spirit Forge",lIe="Toothrow",tIe="Corpsemourn",oIe="Stormchaser",sIe="Gravepalm",cIe="Ghoulhide",mIe="Hellmouth",pIe="Infernostride",dIe="Waterwalk",uIe="Silkweave",gIe="War Traveler",MIe="Razortail",hIe="Gloom's Trap",vIe="Snowclash",HIe="Lance Guard",bIe="Boneflame",AIe="Steel Pillar",xIe="Darkfear",NIe="Dragonscale",fIe="Ravenlore",kIe="Boneshade",CIe="Nethercrow",yIe="Flamebellow",LIe="Death's Fathom",TIe="Wolfhowl",SIe="Stormlash",wIe="Frostwind",DIe="Marrowwalk",PIe="Metalite's Girth",IIe="Giant Skull",EIe="Astreon's Iron Ward",RIe="Drakeflame",BIe="Skulltred",qIe="Rings",GIe="Metalgrid",UIe="Stormshield",OIe="Armor",zIe="Windforce",FIe="Eaglehorn",WIe="Gimmershred",jIe="Widowmaker",_Ie="Stormspire",VIe="Wizardspike",JIe="Doombringer",QIe="Lightsabre",KIe="Hellslayer",YIe="Endlesshail",XIe="Riftlash",$Ie="Credendum",ZIe="Bartuc's Chop Chop",eEe="Annihilus",aEe="Doomseer",rEe="Terra's Guardian",iEe="Triad's Foliage",nEe="Malignant Skull",lEe="Apocrypha",tEe="Homunculus",oEe="Xenos",sEe="Nagas",cEe="%0 %1",mEe=" Kick",pEe=" Kicks",dEe="Pet Life: ",uEe="Wolf Defense: ",gEe="Passive Bonus to Wolves and Bears",MEe=" per hit",hEe=" hit",vEe="%d Percent Chance of Critical Strike",HEe="Mana Cost Per Raven: ",bEe="Kurast Shield",AEe="Hatchet Hands",xEe="Kick Damage: ",NEe="Kick Damage:",fEe="Percent Chance to Cast",kEe="Frozen Anya",CEe="Larzuk will add sockets to the item of your choice.",yEe="Find Nihlathak in the Halls of Vaught.",LEe="Rescue Anya.",TEe="Free the soldiers from their prison and lead them back to town.",SEe="Anya will personalize an item for you.",wEe="Kill Baal in the Worldstone Chamber before he corrupts it.",DEe="Find Baal's Throne Room.",PEe="THE SISTER'S LAMENT",IEe="DESERT JOURNEY",EEe="MEPHISTO'S JUNGLE",REe="ENTER HELL",BEe="TERROR'S END",qEe="SEARCH FOR BAAL",GEe="DESTRUCTION'S END",UEe="Say 'Retreat'",OEe=`Right Click to Cast
Scroll of Resistance`,zEe="Death Mage",FEe="Abaddon",WEe="Pit of Acheron",jEe="Infernal Pit",_Ee=" per blade",VEe="Can be Inserted into Socketed Items",JEe="Kill Baal's Minions.",QEe="%d%% Chance to cast level %d %s on attack",KEe="%d%% Chance to cast level %d %s on striking",YEe="%d%% Chance to cast level %d %s when struck",XEe="Keep in inventory to gain bonus",$Ee="Defensive",ZEe="Offensive",eRe="Combat",aRe="Elemental Charge-up Damage: ",rRe="Retreat!",iRe="Run away!",nRe="So, it begins.",lRe="They'll never see me coming.",tRe="So dark... perfect.",oRe="So, this is where evil hides.",sRe="Whose handiwork lies buried here?",cRe="Planting the dead... How odd.",mRe="Such corruption in this place...",pRe="Evil flows from here.",dRe="Who would want to remember this place?",uRe="I can smell why this tower was abandoned.",gRe="Try and cage me, demons.",MRe="Bars can't hold a force of nature.",hRe="I don't like it down here.",vRe="The supernatural is strong here.",HRe="The Rogues' test is done.",bRe="Bah! Is that all of them?",ARe="What I kill stays dead.",xRe="Your time is past, Blood Raven.",NRe="How has this tree escaped corruption?",fRe="This dead tree teems with energy.",kRe="These stones hold an ancient power.",CRe="Such stones are common back home.",yRe="Tristram... The first to fall to Diablo's wrath.",LRe="Ruins... the fate of all cities.",TRe="Cain! Go to the Rogue camp.",SRe="Deckard Cain, leave this place!",wRe="A Malus! This should go to Charsi.",DRe="Charsi will be thankful to get this Malus.",PRe="Death becomes you, Andariel.",IRe="Your reign is over, Andariel.",ERe="Why must evil hide in such wretched places?",RRe="Face the light or lurk in darkness.",BRe="Vengeance... for Atma.",qRe="Return to dust, Radament.",GRe="An eclipse... never a good omen.",URe="Strange... an unexpected eclipse.",ORe="Dark magic in a darker tomb...",zRe="Snakes... I hate snakes.",FRe="Serpents! I expected worse.",WRe="The sun warms the world once more.",jRe="The Sanctuary - Horazon's obsession.",_Re="This was not designed by nature's Architect.",VRe="Summoner, the dark magics have corrupted you.",JRe="This place would drive anyone mad.",QRe="Horazon. Your decoy is dead.",KRe="Now I can leave this twisted nightmare.",YRe="The Horadrim have left their mark here.",XRe="These Horadric markings are mysterious.",$Re="I can sense Tal Rasha's presence now.",ZRe="So, Tal Rasha... This is your resting place.",eBe="I shall track the Prime Evils to the ends of the world.",aBe="Diablo... I will find you yet.",rBe="Black books make for dark thoughts.",iBe="An ancient manuscript...  This could be useful.",nBe="Ormus... You have strange taste in books.",lBe="Ormus... study the book well.",tBe="And I thought the Forgotten Tower stank.",oBe="This smells worse than the sewers of Lut Gohlein.",sBe="Levers are made to be pulled.",cBe="Finally... The drain lever.",mBe="This is one drain I don't mind cleaning out.",pBe="From trash to treasure...",dBe="What a delicious blade! I should consult Ormus.",uBe="Ormus may know something about this unusual blade.",gBe="Hmm, a jade statue. What should I do with it?",MBe="It looks like jade. Perhaps it's worth something.",hBe="I dread this place of darkness.",vBe="This temple is a nest of evil.",HBe="The dark magic here is dispelled.",bBe="There is hope once again.",ABe="Mephisto... I'm coming for you.",xBe="Hatred stirs within me.",NBe="Mephisto's hatred was a poisonous void.",fBe="Corruption... take flight.",kBe="I have no pity for him. Oblivion is his reward.",CBe="Terror stalks Hell no more.",yBe="Eternal suffering would be too brief for you, Diablo.",LBe="Lord Diablo I have bested you.",TBe="Let Diablo's death end the reign of the Three!",SBe="The reign of Terror has ended.",wBe="A hero's mistake is finally corrected.",DBe="Thus ends the plague of Terror.",PBe="My magic will break the siege.",IBe="The time has come to cleanse my homeland!",EBe="It takes more than a siege to stop me.",RBe="Baal. I'm coming for you.",BBe="The siege must be stopped.",qBe="You'll pay for your atrocities, Baal.",GBe="Baal! Nothing will stand in my way.",UBe="Harrogath can rest easier now.",OBe="The siege is broken.",zBe="My, my, what a messy little demon.",FBe="Harrogath is free of your kind, demon.",WBe="Oops...Did I do that?",jBe="Shenk, your command has ended.",_Be="The catapults have been silenced.",VBe="Could this be a trap?",JBe="A coward's hiding place.",QBe="Ahh, the familiar scent of death.",KBe="By the Light! What is this place?",YBe="...Nihlathak's home away from home.",XBe="I should have known...",$Be="Nihlathak... you can't hide from me.",ZBe="Your power was no match for mine.",eqe="A fitting death for a traitor.",aqe="You were a sad little man, Nihlathak.",rqe="Nihlathak. What led you to this end?",iqe="Conspiring with Baal... What a tragic mistake.",nqe="You Dark Mages are all alike - obsessed with power.",lqe="Betrayer, you've reaped your reward.",tqe="The fabled home of the Ancients.",oqe="The guardians of Mount Arreat await.",sqe="The resting place of the Ancients...",cqe="The summit - The Barbarian holy ground.",mqe="The fabled home of the Ancients.",pqe="I shall prove worthy.",dqe="At last...The summit of Mount Arreat.",uqe="The power of the Worldstone washes over me.",gqe="The halls of the Ancients... Magnificent.",Mqe="So, this is what the Ancients guard.",hqe="The Worldstone! Praise the Light.",vqe="The Worldstone!",Hqe="The Worldstone. What power.",bqe="The legendary Worldstone - guardian of the Natural realm.",Aqe="The last of the Three has fallen.",xqe="The Prime Evils are no more.",Nqe="Baal, never doubt my skills.",fqe="Baal, you shall no longer taint this mortal realm.",kqe="My work here is truly done.",Cqe="The Evil brotherhood is no more.",yqe="Baal! Join your brothers in oblivion.",Lqe="Raven",Tqe="summon ravens",Sqe=`the eyes of your enemies
summon ravens to peck out`,wqe="Raven",Dqe="Werewolf",Pqe="transform into a werewolf",Iqe="transform into a werewolf",Eqe="Werewolf",Rqe="Lycanthropy",Bqe="passive - improves shape-shifting ability",qqe=`when in werewolf or werebear form
passive - improves duration and life`,Gqe="Lycanthropy",Uqe="Firestorm",Oqe="unleash fiery chaos",zqe="unleash fiery chaos to burn your enemies",Fqe="Firestorm",Wqe="Oak Sage",jqe="summon the spirit of the oak",_qe=`life for you and your party
summon a spirit pet that increases`,Vqe="Oak Sage",Jqe="Summon Spirit Wolf",Qqe="summon a wolf",Kqe=`to fight by your side
summon a wolf with teleporting ability`,Yqe="Sum Spt Wolf",Xqe="Werebear",$qe="transform into a werebear",Zqe="transform into a werebear",eGe="Werebear",aGe="Molten Boulder",rGe="launch a molten boulder",iGe=`that knocks back your enemies
launch a boulder of flaming hot magma`,nGe="Molten Boulder",lGe="Arctic Blast",tGe="shoot a jet of ice",oGe=`to burn your enemies with frost
blast a continuous jet of ice`,sGe="Arctic Blast",cGe="Carrion Vine",mGe="summon corpse eating vine",pGe=`and replenishes your life
summon a vine that eats corpses`,dGe="Carrion Vine",uGe="Feral Rage",gGe="life-stealing rage attack - werewolf form",MGe=`with successive hits
increasing amounts of life from your enemies
go into a frenzied rage to steal
when in werewolf form,`,hGe="Feral Rage",vGe="Maul",HGe="maul your enemies - werebear form",bGe=`with successive hits
for increasing extra damage
maul your enemies
when in werebear form,`,AGe="Maul",xGe="Fissure",NGe="open the earth to burn enemies",fGe=`burning them to a crisp
open volcanic vents below your enemies,`,kGe="Fissure",CGe="Cyclone Armor",yGe="shield from elemental damage",LGe=`fire, cold, and lightning
shield yourself from damage caused by`,TGe="Cyclone Armor",SGe="Heart of Wolverine",wGe="summon a wolverine spirit",DGe=`of you and your party
to the damage and attack rating
summon a spirit pet that adds`,PGe="Wolverine Hrt",IGe="Summon Dire Wolf",EGe="summon an enraged wolf",RGe=`it does to enemies
eating corpses to increase damage
summon a wolf that becomes enraged,`,BGe="Summon D Wolf",qGe="Rabies",GGe="bite causes disease - werewolf form",UGe=`that spreads to other monsters
to inflict them with disease
bite your enemies
when in werewolf form,`,OGe="Rabies",zGe="Fire Claws",FGe="fiery, mauling attack",WGe=`with a fiery claw attack
form, maul your enemies
when in werewolf or werebear`,jGe="Fire Claws",_Ge="Twister",VGe="release several small whirlwinds",JGe=`cut a path through your enemies
release several small whirlwinds that`,QGe="Twister",KGe="Solar Creeper",YGe="summon corpse eating vine",XGe=`and replenishes your mana
summon a vine that eats corpses`,$Ge="Sol Creep",ZGe="Hunger",eUe="life-and-mana-stealing bite",aUe=`to gain life and mana
form, bite your enemies
when in werewolf or werebear`,rUe="Hunger",iUe="Shock Wave",nUe="create shock waves - werebear form",lUe=`that stuns nearby enemies
stomp to create a shock wave
when in werebear form,`,tUe="Shock Wave",oUe="Volcano",sUe="create a volcano",cUe=`and destruction over your enemies
summon forth a volcano to rain death`,mUe="Volcano",pUe="Tornado",dUe="create a tornado",uUe=`to blast your enemies
create a funnel of wind and debris`,gUe="Tornado",MUe="Spirit of Barbs",hUe="summon a spirit pet of thorns",vUe=`back at your enemies
taken by you and your party
summon spirit pet that reflects damage`,HUe="Spirit Barbs",bUe="Summon Grizzly",AUe="summon a grizzly bear",xUe="summon a ferocious grizzly bear",NUe="Summon Grizzly",fUe="Fury",kUe="multiple attacks - werewolf Form",CUe=`or one target multiple times
either multiple adjacent targets
when in werewolf form, attack`,yUe="Fury",LUe="Armageddon",TUe="rain fire on your enemies",SUe=`destruction on nearby enemies
create a meteor shower to rain fiery`,wUe="Armageddon",DUe="Hurricane",PUe="create a massive wind storm",IUe=`debris to pound your enemies to bits
create a massive storm of wind and`,EUe="Hurricane",RUe="Fire Blast",BUe="throw a fire bomb",qUe=`to blast your enemies to bits
throw a fire bomb`,GUe="Fire Blast",UUe="Claw Mastery",OUe="passive - improves claw-class weapons ability",zUe=`with claw-class weapons
passive - improves your skill`,FUe="Claw Mastery",WUe="Psychic Hammer",jUe="a mind blast to crush your enemies",_Ue=`to crush and knock back your enemies
to create a psychic blast
use the power of your mind`,VUe="Psyc Hammer",JUe="Tiger Strike",QUe=`increases damage of finishing moves

Charge-up Skill`,KUe=`normal attack to release charges
must use a dragon finishing move or
to finishing moves
consecutive hits add damage bonuses

Charge-up Skill
`,YUe="Tiger Strike",XUe="Dragon Talon",$Ue=`kick your enemies

Finishing Move`,ZUe=`adds charged-up bonuses to the kick
kick your enemies out of your way

Finishing Move
`,eOe="Dragon Talon",aOe="Shock Web",rOe="throw a web of lightning",iOe=`to shock your enemies
throw a web of lightning`,nOe="Shock Web",lOe="Blade Sentinel",tOe="set a spinning blade",oOe=`between you and target point
set a spinning blade to patrol`,sOe="Blade Sentinel",cOe="Burst of Speed",mOe="increases attack and movement speed",pOe=`for a period of time
increases attack and movement speed`,dOe="Burst of Speed",uOe="Fists of Fire",gOe=`adds fire damage to finishing moves

Charge-up Skill`,MOe=`normal attack to release charges
must use a dragon finishing move or
can only be used with claw-class weapons
to finishing moves
consecutive hits add fire damage

Charge-up Skill
`,hOe="Fists of Fire",vOe="Dragon Claw",HOe=`double claw attack

Finishing Move`,bOe=`adds charged-up bonuses to both claw attacks
with your dual claw-class weapons
slice and dice your enemies

Finishing Move
`,AOe="Dragon Claw",xOe="Charged Bolt Sentry",NOe="a trap that emits charged bolts",fOe=`at enemies that pass near
a trap that emits charged bolts`,kOe="Charged Bolt",COe="Wake of Fire",yOe="a trap that emits waves of fire",LOe="a trap that emits waves of fire",TOe="Wake of Fire",SOe="Weapon Block",wOe="passive - block with two claw-class weapons",DOe=`you are using dual claw-class weapons
passive - chance to block when`,POe="Wpn Block",IOe="Cloak of Shadows",EOe="blind your enemies",ROe=`lowering their defenses for a period of time
cast a shadow to blind nearby enemies`,BOe="Cloak of Shdws",qOe="Cobra Strike",GOe=` adds life and mana stealing to finishing moves

Charge-up Skill`,UOe=`normal attack to release charges
must use a dragon finishing move or
to finishing moves
consecutive hits add life and mana stealing

Charge-up Skill
`,OOe="Cobra Strike",zOe="Blade Fury",FOe="throw spinning blades",WOe=`to slice up your enemies
throw spinning blades`,jOe="Blade Fury",_Oe="Fade",VOe="temporary resist all",JOe=`for a period of time
raise all resistances and resist curses`,QOe="Fade",KOe="Shadow Warrior",YOe="summon a shadow of yourself",XOe=`your skills and fights by your side
summon a shadow of yourself that mimics`,$Oe="Shdw Warrior",ZOe="Claws of Thunder",eze=`adds lightning damage to finishing moves
 
Charge-up Skill`,aze=`normal attack to release charges
must use a dragon finishing move or
can only be used with claw-class weapons
to finishing moves
consecutive hits add lightning damage

Charge-up Skill
`,rze="Thunder Claws",ize="Dragon Tail",nze=`explosive kick

Finishing Move`,lze=`adds charged-up bonuses to the kick
knock back your enemies with an explosive kick

Finishing Move
`,tze="Dragon Tail",oze="Lightning Sentry",sze="a trap that emits lightning",cze=`to scorch passing enemies
a trap that shoots lightning`,mze="Lightning Sentry",pze="Wake of Inferno",dze="trap that sprays fire",uze="trap that sprays fire at passing enemies",gze="Wake of Inferno",Mze="Mind Blast",hze="compelling psionic blast",vze=`and convert the feeble-minded
stun a group of enemies
using the power of your mind`,Hze="Mind Blast",bze="Blades of Ice",Aze=`adds cold damage to finishing moves

Charge-up Skill`,xze=`normal attack to release charges
must use a dragon finishing move or
can only be used with claw-class weapons
to finishing moves
consecutive hits add cold damage

Charge-up Skill
`,Nze="Blades of Ice",fze="Dragon Flight",kze=`teleport and kick enemies

Finishing Move`,Cze=`adds charged-up bonuses to the kick
and destroy them with a kick
teleport to your enemies

Finishing Move
`,yze="Dragon Flight",Lze="Death Sentry",Tze="trap that explodes nearby corpses",Sze=`or explodes nearby corpses laying waste to more enemies
trap that shoots lightning at your enemies`,wze="Death Sentry",Dze="Blade Shield",Pze="spinning blades of defense",Ize=`who stray too close
spinning blades slice enemies`,Eze="Blade Shield",Rze="Venom",Bze="poison your weapon",qze="add poison damage to your weapons",Gze="Venom",Uze="Shadow Master",Oze="summon your shadow",zze=`to fight by your side
summon a powerful shadow of yourself`,Fze="Shdw Master",Wze="Phoenix Strike",jze=`adds elemental novas to finishing moves

Charge-up Skill`,_ze=`normal attack to release charges
must use a dragon finishing move or
adds elemental novas to finishing moves

Charge-up Skill
`,Vze="Phnx Strike",Jze=" per kick",Qze="Life Steal: ",Kze="Chance to stun: ",Yze="Chance to afflict target: ",Xze="Charge 1 - ",$ze="Charge 2 - ",Zze="Charge 3 - ",eFe="Adds ",aFe="Finishing Move Bonuses",rFe=" percent life stealing",iFe=" percent life and mana stealing ",nFe="burning damage",lFe=" percent damage",tFe="Lowers Resistance ",oFe=" to melee attacks",sFe="Mana Steal: ",cFe="Feral Pets: ",mFe=" Percent Attack",pFe=" Percent Life",dFe=" Percent Damage",uFe="Finishing Move - ",gFe="Mana Recovered: ",MFe="meteor damage: ",hFe="chain lightning damage: ",vFe="chaos ice bolt damage: ",HFe="lightning damage: ",bFe="nova damage: ",AFe="charged bolt damage: ",xFe="fire damage: ",NFe="fire damage radius: ",fFe="burning duration: ",kFe="cold damage: ",CFe="cold damage radius: ",yFe="freeze duration: ",LFe="Raven",TFe="Wolf",SFe="Bear",wFe="Poison Creeper",DFe="Carrion Vine",PFe="Solar Creeper",IFe="Spirit of Barbs",EFe="Heart of Wolverine",RFe="Vine",BFe="Spirit",qFe="Dire Wolf",GFe="Warrior",UFe="Shadow",OFe="Master",zFe="Eagle",FFe="Wolf",WFe="Bear",jFe="Catapult",_Fe="Catapult",VFe="Catapult",JFe="Catapult",QFe="Catapult",KFe="Snow Drifter",YFe="Abominable",XFe="Chilled Froth",$Fe="Frozen Abyss",ZFe="Warped Fallen Wolfrider",eWe="Darkone Wolfrider",aWe="Devilkin Wolfrider",rWe="Carver Wolfrider",iWe="Fallen Wolfrider",nWe="Ghostly",lWe="Fanatic",tWe="Possessed",oWe="Berserker",sWe="Larzuk",cWe="Anya",mWe="Malah",pWe="Nihlathak",dWe="Barbarian Captive",uWe="Moe",gWe="Curly",MWe="Larry",hWe="Pindleskin",vWe="Frozenstein",HWe="(Druid Only)",bWe="(Assassin Only)",AWe="(Amazon Only)",xWe="(Barbarian Only)",NWe="Summoning",fWe="Shape",kWe="Shifting",CWe="Elemental",yWe="Traps",LWe="Shadow",TWe="Disciplines",SWe="Martial",wWe="Arts",DWe="Chest",PWe="Wooden Chest",IWe="Burial Chest",EWe="Burial Chest",RWe="Chest",BWe="Chest",qWe="Chest",GWe="Wooden Chest",UWe="Chest",OWe="Pyre of Flesh",zWe="Burning Pit",FWe="Town Flag",WWe="Chandelier",jWe="Jar",_We="Jar",VWe="Jar",JWe="Swinging Heads",QWe="Pole",KWe="Skulls and Rocks",YWe="Hell Gate",XWe="Main Gate",$We="Banner",ZWe="Banner",eje="Pole",aje="Stash",rje="Debris",ije="Wooden Chest",nje="Wooden Chest",lje="Hidden Stash",tje="Torch",oje="Torch",sje="Tomb",cje="Tomb",mje="Tomb",pje="Torch",dje="Torch",uje="Torch",gje="Smoke",Mje="Dead Barbarian",hje="Dead Barbarian",vje="Cage",Hje="Shrine",bje="Jar",Aje="Jar",xje="Jar",Nje="Jar",fje="Evil Urn",kje="Altar",Cje="Death Pole",yje="Death Pole",Lje="Chest",Tje="Skulls and Rocks",Sje="Jar",wje="Torch",Dje="Torch",Pje="Fire",Ije="Torch",Eje="Health Shrine",Rje="Barrel",Bje="Hidden Stash",qje="Shrine",Gje="Shrine",Uje="Fire Pit",Oje="Torch Pit",zje="Hidden Stash",Fje="Hidden Stash",Wje="Box",jje="Tomb",_je="Tomb",Vje="Tomb",Jje="Tomb",Qje="Tomb",Kje="Corpse",Yje="Candles",Xje="Shrub",$je="Shrub",Zje="Corpse",e_e="Altar of the Heavens",a_e="Hidden Stash",r_e="Weapon Rack",i_e="Weapon Rack",n_e="Armor Stand",l_e="Armor Stand",t_e="Siege on Harrogath",o_e="Stop the Siege by killing Shenk the Overseer in the Bloody Foothills.",s_e="Kill Shenk the Overseer.",c_e="Go talk to Larzuk for your reward.",m_e="Rescue on Mount Arreat",p_e="Find the Soldiers in the Frigid Highlands.",d_e="Rescue %d more Soldiers in the Frigid Highlands.",u_e="Return to Qual-Kehk for your reward.",g_e="Apply the Runes to a Socketed item in this order:",M_e="Prison of Ice",h_e="Look for Anya under the Crystalline Passage by the Frozen River.",v_e="Talk to Malah.",H_e="Use the potion Malah gave you to thaw Anya.",b_e="Talk to Malah for your reward.",A_e="Talk to Anya.",x_e="Betrayal of Harrogath",N_e="Take Anya's portal to Nihlathak's Temple.",f_e="Kill Nihlathak.",k_e="Talk to Anya before you continue through the Crystalline Passage, past the Glacial Trail, to proceed up Mount Arreat to the Summit.",C_e="Rite of Passage",y_e="Travel through the Ancient's Way to find the Ancients at the Arreat Summit.",L_e="Consult with the Ancients by activating the Altar of the Heavens.",T_e="Defeat all three Ancients without leaving Mount Arreat.",S_e="Eve of Destruction",w_e="Consult with the Ancients.",D_e="Kill Baal.",P_e="Talk to Tyreal.",I_e="Take Tyreal's Portal to Safety.",E_e="Harrogath",R_e="Drop Potion on Portrait to Heal",B_e="Right-click to Open Inventory (%s)",q_e="Dismiss",G_e="Dismiss Hireling",U_e="Rehire",O_e="Resurrect",z_e="Resurrect %s: %d",F_e="Thanks.",W_e="Thank you.",j_e="I needed that.",__e="It is good to work for someone who cares.",V_e="Good for you.",J_e="I sense danger.",Q_e="I hate these vermin.",K_e="I have a bad feeling about this.",Y_e="Beware!",X_e="I detest spiders.",$_e="Eek, snakes!",Z_e="I am more experienced.",eVe="I am hurt!",aVe="Help!",rVe="I am dying.",iVe="Help me!",nVe="Good morning.",lVe="Good afternoon.",tVe="Good evening.",oVe="Hello.",sVe="Skill 9",cVe="Skill 10",mVe="Skill 11",pVe="Skill 12",dVe="Skill 13",uVe="Skill 14",gVe="Skill 15",MVe="Skill 16",hVe="Toggle MiniMap",vVe="Swap Weapons",HVe="Hireling Screen",bVe="Hireling Inventory",AVe="Hireling",xVe="add sockets",NVe="personalize",fVe="Choose the item to which you wish to add sockets.",kVe="Varaya",CVe="Khan",yVe="Klisk",LVe="Bors",TVe="Brom",SVe="Wiglaf",wVe="Hrothgar",DVe="Scyld",PVe="Healfdane",IVe="Heorogar",EVe="Halgaunt",RVe="Hygelac",BVe="Egtheow",qVe="Bohdan",GVe="Wulfgar",UVe="Hild",OVe="Heatholaf",zVe="Weder",FVe="Vikhyat",WVe="Unferth",jVe="Sigemund",_Ve="Heremod",VVe="Hengest",JVe="Folcwald",QVe="Frisian",KVe="Hnaef",YVe="Guthlaf",XVe="Oslaf",$Ve="Yrmenlaf",ZVe="Garmund",eJe="Lanth",aJe="Eadgils",rJe="Onela",iJe="Damien",nJe="Tryneus",lJe="Klar",tJe="Wulf",oJe="Bulwye",sJe="Lief",cJe="Magnus",mJe="Klatu",pJe="Drus",dJe="Hoku",uJe="Kord",gJe="Uther",MJe="Ip",hJe="Ulf",vJe="Tharr",HJe="Kaelim",bJe="Ulric",AJe="Alaric",xJe="Ethelred",NJe="Caden",fJe="Elgifu",kJe="Tostig",CJe="Alcuin",yJe="Emund",LJe="Sigurd",TJe="Gorm",SJe="Hollis",wJe="Ragnar",DJe="Torkel",PJe="Wulfstan",IJe="Alban",EJe="Barloc",RJe="Bill",BJe="Theodoric",qJe="Bartuc's Cut-Throat",GJe="Fire Damage Reduced by",UJe="Cold Damage Reduced by",OJe="Lightning Damage Reduced by",zJe="Poison Damage Reduced by",FJe="Absorbs Magic Damage",WJe="Absorbs Fire Damage",jJe="Absorbs Cold Damage",_Je="Absorbs Lightning Damage",VJe="Absorbs Poison Damage",JJe="Void",QJe=" to your attack",KJe="+%d to Javelin and Spear Skills",YJe="+%d to Passive and Magic Skills",XJe="+%d to Bow and Crossbow Skills",$Je="+%d to Defensive Auras",ZJe="+%d to Offensive Auras",eQe="+%d to Summoning Skills",aQe="+%d to Poison and Bone Skills",rQe="+%d to Curses",iQe="+%d to Warcries",nQe="+%d to Combat Skills",lQe="+%d to Masteries",tQe="+%d to Cold Skills",oQe="+%d to Lightning Skills",sQe="+%d to Fire Skills",cQe="+%d to Summoning Skills",mQe="+%d to Shape Shifting Skills",pQe="+%d to Elemental Skills",dQe="+%d to Traps",uQe="+%d to Shadow Disciplines",gQe="+%d to Martial Arts",MQe="No Magic, Socketed, Rare, Unique, or Set Items. No Jewelry.",hQe="Undead",vQe="Demon",HQe="",bQe="",AQe="Immune to Fire",xQe="Immune to Cold",NQe="Immune to Lightning",fQe="Immune to Poison",kQe="Immune to Physical",CQe="Immune to Magic",yQe="%s's",LQe="%s'",TQe="%0",SQe="The EXPANSION LADDER displays the top characters, ranked by experience. The default setting displays overall rankings, but you can view sorted lists after selecting the By Class option.",wQe="The EXPANSION HARDCORE LADDER displays the top Hardcore characters, ranked by experience. The default setting displays overall rankings, but you can view sorted lists after selecting By Class option.",DQe="Druid",PQe="Assassin",IQe="Druid",EQe="Assassin",RQe="%s: %d%%",BQe="Average chance %s will hit you: %d%%",qQe=`Chance to Block: %d%%
Average chance %s will hit you: %d%%`,GQe="%s permits you to loot his corpse.",UQe="%s permits you to loot her corpse.",OQe="%s no longer allows you to access his corpse.",zQe="%s no longer allows you to access her corpse.",FQe="You are hostile towards each other.",WQe="%s is hostile to you, but you are friendly to him.",jQe="%s is hostile to you, but you are friendly to her.",_Qe="%s is friendly to you, but you are hostile to her.",VQe="You are friendly to each other.",JQe="You may loot each other's corpse.",QQe="%s may loot your corpse, but you may not loot his.",KQe="%s may loot your corpse, but you may not loot hers.",YQe="%s may not loot your corpse, but you may loot his.",XQe="%s may not loot your corpse, but you may loot hers.",$Qe="Neither of you may loot the other's corpse.",ZQe=" ",eKe=" ",aKe=" ",rKe=" ",iKe=" ",nKe=" ",lKe=" ",tKe=" ",oKe=" ",sKe=" ",cKe=" ",mKe=" ",pKe=" ",dKe=" ",uKe=" ",gKe=" ",MKe=" ",hKe=" ",vKe=" ",HKe=" ",bKe=" ",AKe=" ",xKe=" ",NKe=" ",fKe=" ",kKe=" ",CKe=" ",yKe=" ",LKe=" ",TKe=" ",SKe=`or bolts with fire
magically enhances your arrows`,wKe=" ",DKe=" ",PKe=" ",IKe=`cold arrows only do half of their regular damage
by adding cold damage and a slowing effect
magically enhances your arrows or bolts`,EKe=" ",RKe=" ",BKe=" ",qKe=" ",GKe=" ",UKe=" ",OKe=" ",zKe=" ",FKe=" ",WKe=" ",jKe=" ",_Ke=`cold arrows only do half of their regular damage
by adding cold damage and a slowing effect
magically enhances your arrows or bolts`,VKe=" ",JKe=" ",QKe=" ",KKe=" ",YKe=" ",XKe=" ",$Ke=" ",ZKe=" ",eYe=" ",aYe=" ",rYe=" ",iYe=" ",nYe=" ",lYe=" ",tYe=" ",oYe=" ",sYe=" ",cYe=" ",mYe=" ",pYe=`contact, damaging all nearby enemies
enchants an arrow or bolt that explodes on`,dYe=" ",uYe=" ",gYe=" ",MYe=" ",hYe=" ",vYe=" ",HYe=" ",bYe=" ",AYe=" ",xYe=" ",NYe=" ",fYe=" ",kYe=" ",CYe=" ",yYe=" ",LYe=" ",TYe=" ",SYe=" ",wYe=" ",DYe=`to freeze your enemies
magically enhances your arrow or bolt`,PYe=" ",IYe=" ",EYe=" ",RYe=" ",BYe=" ",qYe=" ",GYe=" ",UYe=" ",OYe=" ",zYe=" ",FYe=" ",WYe=" ",jYe=" ",_Ye=" ",VYe=" ",JYe=" ",QYe=" ",KYe=" ",YYe=" ",XYe=" ",$Ye=" ",ZYe=" ",eXe=" ",aXe=`creates a pyre upon impact
cause severe fire damage and
enhances arrows or bolts to`,rXe=" ",iXe=" ",nXe=" ",lXe=" ",tXe=" ",oXe=" ",sXe=" ",cXe=" ",mXe=" ",pXe=" ",dXe=" ",uXe=" ",gXe=" ",MXe=" ",hXe=" ",vXe=`to freeze entire groups of monsters
magically enhances an arrow or bolt`,HXe=" ",bXe=" ",AXe=" ",xXe=" ",NXe=" ",fXe=" ",kXe=" ",CXe=" ",yXe=" ",LXe=" ",TXe=" ",SXe=" ",wXe=" ",DXe=" ",PXe=" ",IXe=" ",EXe=" ",RXe=" ",BXe=" ",qXe=" ",GXe=" ",UXe=" ",OXe=" ",zXe=" ",FXe=" ",WXe=" ",jXe=" ",_Xe=" ",VXe=" ",JXe=" ",QXe=" ",KXe=" ",YXe=" ",XXe=" ",$Xe=" ",ZXe=" ",e$e=" ",a$e=" ",r$e=" ",i$e=" ",n$e=" ",l$e=" ",t$e=" ",o$e=`of all nearby enemies
creates an electrical field that reduces life`,s$e=" ",c$e=" ",m$e=" ",p$e=" ",d$e=" ",u$e=" ",g$e=" ",M$e=" ",h$e=" ",v$e=" ",H$e=" ",b$e=" ",A$e=" ",x$e=" ",N$e=" ",f$e=" ",k$e=" ",C$e=" ",y$e=" ",L$e=" ",T$e=" ",S$e=" ",w$e=" ",D$e=" ",P$e=" ",I$e=" ",E$e=" ",R$e=" ",B$e=" ",q$e=" ",G$e=" ",U$e=" ",O$e=" ",z$e=" ",F$e=" ",W$e=" ",j$e=" ",_$e=" ",V$e=" ",J$e=" ",Q$e=" ",K$e=" ",Y$e=" ",X$e=" ",$$e=" ",Z$e=" ",eZe=" ",aZe=" ",rZe=" ",iZe=" ",nZe=" ",lZe=" ",tZe=" ",oZe=" ",sZe=" ",cZe=" ",mZe=" ",pZe=" ",dZe=" ",uZe=" ",gZe=" ",MZe=" ",hZe=" ",vZe=" ",HZe=" ",bZe=" ",AZe=" ",xZe=" ",NZe=" ",fZe=" ",kZe=" ",CZe=" ",yZe=" ",LZe=" ",TZe=" ",SZe=" ",wZe=" ",DZe=" ",PZe=" ",IZe=" ",EZe=" ",RZe=" ",BZe="passive - increases lightning damage",qZe="passive - increases all damage caused by your lightning spells",GZe=" ",UZe=" ",OZe=" ",zZe=" ",FZe=" ",WZe=" ",jZe=" ",_Ze=" ",VZe=" ",JZe=" ",QZe=" ",KZe=" ",YZe=" ",XZe=" ",$Ze=" ",ZZe=" ",eea=" ",aea=" ",rea=" ",iea=" ",nea=" ",lea=" ",tea=" ",oea=" ",sea=" ",cea=" ",mea=" ",pea=" ",dea=" ",uea=" ",gea=" ",Mea=" ",hea=" ",vea=" ",Hea=" ",bea=" ",Aea=" ",xea=" ",Nea=" ",fea=" ",kea=" ",Cea=" ",yea=" ",Lea=" ",Tea=" ",Sea=" ",wea=" ",Dea=" ",Pea=" ",Iea=" ",Eea=" ",Rea=" ",Bea=" ",qea=" ",Gea=" ",Uea=" ",Oea=" ",zea=" ",Fea=" ",Wea=" ",jea=" ",_ea=" ",Vea=" ",Jea=" ",Qea=" ",Kea=" ",Yea=" ",Xea=" ",$ea=" ",Zea=" ",eaa=" ",aaa=" ",raa=" ",iaa=" ",naa=" ",laa=" ",taa=" ",oaa=" ",saa=" ",caa=" ",maa=" ",paa=" ",daa=" ",uaa=" ",gaa=" ",Maa=" ",haa=" ",vaa=" ",Haa=" ",baa=" ",Aaa=" ",xaa=`this curse may not be overridden by another curse
target of all nearby monsters
curses a monster to become the`,Naa=" ",faa=" ",kaa=" ",Caa=" ",yaa=" ",Laa=" ",Taa=" ",Saa=" ",waa=" ",Daa=" ",Paa=" ",Iaa=" ",Eaa=" ",Raa=" ",Baa=" ",qaa=" ",Gaa=" ",Uaa=" ",Oaa=" ",zaa=" ",Faa=" ",Waa=" ",jaa=" ",_aa=" ",Vaa=" ",Jaa=" ",Qaa=" ",Kaa=" ",Yaa=" ",Xaa=" ",$aa=" ",Zaa=" ",era=" ",ara=" ",rra=" ",ira=" ",nra=" ",lra=" ",tra=" ",ora=" ",sra=" ",cra=" ",mra=" ",pra=" ",dra=" ",ura=" ",gra=" ",Mra=" ",hra=" ",vra=" ",Hra=" ",bra=" ",Ara=" ",xra=" ",Nra=" ",fra=" ",kra=" ",Cra=" ",yra=" ",Lra=" ",Tra=" ",Sra=" ",wra=" ",Dra=" ",Pra=" ",Ira=" ",Era=" ",Rra=" ",Bra=" ",qra=" ",Gra=" ",Ura=" ",Ora=" ",zra=" ",Fra=" ",Wra=" ",jra=" ",_ra=" ",Vra=" ",Jra=" ",Qra=" ",Kra=" ",Yra=" ",Xra=" ",$ra=" ",Zra=" ",eia=" ",aia=" ",ria=" ",iia=" ",nia=" ",lia=" ",tia=" ",oia=" ",sia=" ",cia=" ",mia=" ",pia=" ",dia=" ",uia=" ",gia=" ",Mia=" ",hia=" ",via=" ",Hia=" ",bia=" ",Aia=" ",xia=" ",Nia=" ",fia=" ",kia=" ",Cia=" ",yia=" ",Lia=" ",Tia=" ",Sia=" ",wia=" ",Dia=" ",Pia=" ",Iia=" ",Eia=" ",Ria=" ",Bia=" ",qia=" ",Gia=" ",Uia=" ",Oia=" ",zia=`adds lightning damage to your attack
to damage nearby enemies
when active, aura causes pulses of electricity`,Fia=" ",Wia=" ",jia=" ",_ia=" ",Via=" ",Jia=" ",Qia=" ",Kia=" ",Yia=" ",Xia=" ",$ia=" ",Zia=" ",ena=" ",ana=" ",rna="aura - increases attack speed and damage",ina=`and attack rating for you and your party
when active, aura increases damage, attack speed,`,nna=" ",lna=" ",tna="aura - weakens enemies",ona=" ",sna=" ",cna=" ",mna=" ",pna=`you life and mana
the souls of slain enemies to give
when active, aura attempts to redeem`,dna=" ",una=" ",gna=" ",Mna=" ",hna=" ",vna=" ",Hna=" ",bna=" ",Ana=" ",xna=" ",Nna=" ",fna=" ",kna=" ",Cna=" ",yna=" ",Lna=" ",Tna=" ",Sna=" ",wna=" ",Dna=" ",Pna=" ",Ina=" ",Ena=" ",Rna=" ",Bna=" ",qna=" ",Gna=" ",Una=" ",Ona=" ",zna=" ",Fna=" ",Wna=" ",jna=" ",_na=" ",Vna=" ",Jna=" ",Qna=" ",Kna=" ",Yna=" ",Xna=" ",$na=" ",Zna=" ",ela=" ",ala=" ",rla=" ",ila=" ",nla=" ",lla=" ",tla=" ",ola=" ",sla=" ",cla=" ",mla=" ",pla=" ",dla=" ",ula=" ",gla=" ",Mla=" ",hla=" ",vla=" ",Hla=" ",bla=" ",Ala=" ",xla=" ",Nla=" ",fla=" ",kla=" ",Cla=" ",yla=" ",Lla=" ",Tla=" ",Sla=" ",wla=" ",Dla=" ",Pla=" ",Ila=" ",Ela=" ",Rla=" ",Bla=" ",qla=" ",Gla=" ",Ula=" ",Ola=" ",zla=" ",Fla=" ",Wla=" ",jla=" ",_la=" ",Vla=" ",Jla=" ",Qla=" ",Kla=" ",Yla=" ",Xla=" ",$la=" ",Zla=" ",eta=" ",ata=" ",rta=" ",ita=" ",nta=" ",lta=" ",tta=" ",ota=" ",sta=" ",cta=" ",mta=" ",pta=" ",dta=" ",uta=" ",gta=" ",Mta=" ",hta=" ",vta=" ",Hta=" ",bta=" ",Ata=" ",xta=" ",Nta=" ",fta=" ",kta=" ",Cta=" ",yta=" ",Lta=" ",Tta=" ",Sta="You must wait a short time to declare hostility with that player.",wta="CHAT",Dta="NEWS",Pta="LADDER",Ita="LADDER CHARACTER",Eta="%s Receives Bonuses From:",Rta="Damage per Level",Bta="Elemental Damage per Level",qta="Fire Damage per Level",Gta="Cold Damage per Level",Uta="Lightning Damage per Level",Ota="Poison Damage per Level",zta="Magic Damage per Level",Fta="Yards per Level",Wta="Rate of Fire per Level",jta="Attack Rating per Level",_ta="Attack Speed per Level",Vta="Defense per Level",Jta="Mana Cost per Level",Qta="Missiles per Level",Kta="+1 Missile per Level",Yta="+1 Missile per %d Levels",Xta="Bolts per Level",$ta="+1 Bolt per Level",Zta="+1 Bolt per %d Levels",eoa="Shots per Level",aoa="+1 Shot per Level",roa="+1 Shot per %d Levels",ioa="Life per Level",noa="Walk/Run Speed per Level",loa="Duration per Level",toa="Cold Length per Level",ooa="Freeze Length per Level",soa="Poison Length per Level",coa="Converts %d%% Physical Damage to Magic Damage per Level",moa="Converts %d%% Physical Damage to Elemental Damage per Level",poa="Converts %d%% Physical Damage to Elemental Damage",doa="Converts %d%% Physical Damage to Magic Damage",uoa="Second per Level",goa="Seconds per Level",Moa="Damage Absorbed per Level",hoa="Weapon Damage",voa="Holy Bolt Damage per Level",Hoa="Life Healed per Level",boa="Life Healed Every 2 Seconds",Aoa="Your Damage: ",xoa="Party Damage: ",Noa="Average Fire Damage per Second per Level",foa="Slows Enemies: ",koa="Corpse Explosion Damage: ",Coa="Level %d %s Aura When Equipped",yoa="to all Attributes",Loa="to Experience Gained",Toa="Life after each Kill",Soa="Reduces all Vendor Prices",woa="Slain Monsters Rest in Peace",Doa="to Attack Rating versus",Poa="to Damage versus",Ioa="Slaying:",Eoa="Reanimate as:",Roa="to Enemy Cold Resistance",Boa="to Enemy Fire Resistance",qoa="to Enemy Lightning Resistance",Goa="to Enemy Poison Resistance",Uoa="to Fire Skill Damage",Ooa="to Cold Skill Damage",zoa="to Lightning Skill Damage",Foa="to Poison Skill Damage",Woa="%d%% Chance to cast level %d %s when you Die",joa="%d%% Chance to cast level %d %s when you Level-Up",_oa="%d%% Chance to cast level %d %s when you Kill an Enemy",Voa="Werewolf",Joa="transform into a werewolf",Qoa="transform into a werewolf",Koa="Werewolf",Yoa=" skeleton mage",Xoa=" skeleton magi",$oa="+%d to Summoning Skills",Zoa="%d Stones of Jordan Sold to Merchants",esa="Diablo Walks the Earth",asa="Hellspawn Skull",rsa="Trap Door",isa="Legendary Mallet",nsa=`your life and mana
the souls of slain enemies to give
when active, aura attempts to redeem`,lsa="Fiend",tsa="Wraith",osa="Chance to Block: ",ssa="over ",csa="Explore Tal Rasha's Tomb",msa="/reply",psa="Allows you to reply to a whisper without typing the account name",dsa="\xFFc9 Yellow Text\xFFc4 represents special messages sent directly from battle.net",usa="Game Time:",gsa="You must use *account names for anyone on battle.net including people in a different game such as Starcraft.",Msa="\xFFc5Gray Text\xFFc4 also represents actions that have been taken by people in the chat Channel.",hsa="\xFFc3Blue Text\xFFc4 represents special messages sent directly from battle.net or messages from a Blizzard Representative.",vsa="Helms:",Hsa="Shields:",bsa="Weapons:",Asa="Armor:",xsa="EXPANSION CHARACTER",Nsa="Lowers Resistance ",fsa="Can be Inserted into Socketed Items",ksa=" to melee attacks",Csa="%d Percent Chance of Critical Strike",ysa="Say 'Retreat'",Lsa="Ghostly",Tsa="Fanatic",Ssa="Possessed",wsa="Berserker",Dsa="Defensive",Psa="Offensive",Isa="Combat",Esa="(Based on Character Level)",Rsa="Rank",Bsa="Key of Terror",qsa="Key of Hate",Gsa="Key of Destruction",Usa="Diablo's Horn",Osa="Baal's Eye",zsa="Mephisto's Brain",Fsa="Standard of Heroes",Wsa="Lilith",jsa=`Right-click to reset Stat/Skill Points
`)}),T+=te*ie)}),T&&p.push({name:ia[R.LevelName]+[" [N]"," [NM]"," [H]"][S],chance:T,tooltip:["Id: "+R.Id,"mlvl: "+R[["MonLvlEx","MonLvlEx(N)","MonLvlEx(H)"][S]]||0,"Act: "+(R.Id>=109?5:R.Id>=103?4:R.Id>=75?3:R.Id>=40?2:1)].filter(Boolean).join(`
`)}),l.progress+=C,await i(0)}}p=p.sort((S,Z)=>Z.chance-S.chance),u=u.sort((S,Z)=>Z.chance-S.chance),l.areaResults.push(...p),l.packResults.push(...u),l.calculating=!1}}function Me(p,u,g,...C){if(u&&fr[u]){let S=0;return fr[u].counts.forEach((Z,ne)=>{S+=fr[u][g?"droprate":"droprateRoot"][s.value]*Z*Me(p,ne,!0,u,...C)}),S}return p(u,...C)}function le(p,u,g){let C=a(u);[0,1,2].forEach(S=>{if(S&&!p[C("MonUMin")]&&!p[C("MonUMax")])return;let Z=ne=>p[(u?"nmon":S?"umon":"mon")+ne];for(let ne=1;ne<=9;ne++)if(Z(ne)){let R=Ta[Z(ne)];if(R.enabled&&R.killable){let T=ce(R,p,u)+[0,2,3][S];g(R,T,S)}}})}function Y(...p){return p.reduce((u,g)=>u+g,0)/p.length||0}function ce(p,u,g){if(!g)return p.Level||0;let C=a(g),S=u[["MonLvl1Ex","MonLvl2Ex","MonLvl3Ex"][g]]||0,Z=p[C("Level")]||0;return S>Z?S:Z}zi.forEach(p=>{p.func={unique:A(p.Unique,p.UniqueDivisor,p.UniqueMin,250),set:A(p.Set,p.SetDivisor,p.SetMin,500),rare:A(p.Rare,p.RareDivisor,p.RareMin,600),magic:A(p.Magic,p.MagicDivisor,p.MagicMin),hq:A(p.HiQuality,p.HiQualityDivisor),normal:A(p.Normal,p.NormalDivisor)}}),[0,1,2].forEach(p=>{let u=a(p);Nr.forEach(g=>{let C=S=>g[S]||0;if(g.calc=g.calc||{},g.calc.monsters=g.calc.monsters||[],g.calc.monsters[p]=g.calc.monsters[p]||[],g.Id){let S=fva.filter(F=>F.areaId==g.Id||F.hcIdx===19&&[66,67,68,69,70,71,72].includes(g.Id|0)),Z=Ta.filter(F=>F.areaId==g.Id),ne=Gi[g.Id]&&Gi[g.Id][p]||0,R=S.reduce((F,ie)=>F+1+p+((ie.MinGrp||0)+(ie.MaxGrp||0))/2,0),T=Z.reduce((F,ie)=>F+1+ +((ie.MinGrp||0)+(ie.MaxGrp||0))/2,0),P=Y(C(u("MonUMin")),C(u("MonUMax")))*.8*5.5,I=Y(C(u("MonUMin")),C(u("MonUMax")))*.2*3,Ee=ne-P-I-R-T;if(Ee>0){let F=0,ie=0;le(g,p,(te,Oe,Re)=>{if(!Re){let ye=Ae=>te[Ae]||0;F+=Y(ye("PartyMin")+ye("PartyMax"),ye("MinGrp")+ye("MaxGrp"))}Re===2&&ie++}),le(g,p,(te,Oe,Re)=>{let ye=[Ee/F,I/3/ie,P/5.5/ie][Re];g.calc.monsters[p].push({mon:te,mlvl:Oe,type:Re,packCount:ye})})}S.forEach(F=>{let ie=Ta[F.Class],te=ce(ie,g,p)+3;g.calc.monsters[p].push({mon:ie,mlvl:te,type:3,packCount:F.hcIdx===19?1/7:1,superMon:F})}),Z.forEach(F=>{let ie=ce(F,g,p);g.calc.monsters[p].push({mon:F,mlvl:ie,type:4,packCount:1})})}})}),Object.values(FTa).sort((p,u)=>(p=p.code,u=u.code,p<u?-1:p>u?1:0)).forEach(p=>{let u=Oi[p.type],g=ia[p.code]||p.name,C=p.ubercode&&p.code===p.ubercode,S=p.ultracode&&p.code===p.ultracode,Z=p.normcode&&p.code!==p.normcode,ne=u.Class,R=Object.values(zi).filter(T=>T.Version&&!Z==!T.Uber&&!ne==!T["Class Specific"])[0].func;if(["pk1","pk2","pk3","bet","ceh","fed","tes"].includes(p.code)&&(p.spawnable=!0,u.Normal=!0),!(!p.spawnable||p.code==="gld")){if(Fi.forEach(T=>{if(T.code===p.code&&T.enabled){let P=ia[T.index]||T.index,I=Math.max(p.level||0,T.lvl||0);l.items.push({quality:"unique",code:T.code,item:p,type:u,level:I,name:P+" [Unique]",searchable:[P,g,"Unique",T.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" "),tooltip:["Type: "+g,"Code: "+T.code,"Level: "+I,"Keywords: "+[P,g,"Unique",T.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" ")].join(`
`),use:!1,unique:T,func:R})}}),Wi.forEach(T=>{if(T.item===p.code){let P=ia[T.index]||T.index,I=Math.max(p.level||0,T.lvl||0);l.items.push({quality:"set",code:T.item,item:p,type:u,level:I,name:P+" [Set]",searchable:[P,g,"Set",T.item,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" "),tooltip:["Type: "+g,"Code: "+T.item,"Level: "+I,"Keywords: "+[P,g,"Set",T.item,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" ")].join(`
`),use:!1,set:T,func:R})}}),u.Rare){let T=p.level||0;l.items.push({quality:"rare",code:p.code,item:p,type:u,level:T,name:g+" [Rare]",searchable:[g,"Rare",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" "),tooltip:["Code: "+p.code,"Level: "+T,"Keywords: "+[g,"Rare",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" ")].join(`
`),use:!1,func:R})}if(!u.Normal){let T=p.level||0;l.items.push({quality:"magic",code:p.code,item:p,type:u,level:T,name:g+" [Magic]",searchable:[g,"Magic",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" "),tooltip:["Code: "+p.code,"Level: "+T,"Keywords: "+[g,"Magic",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" ")].join(`
`),use:!1,func:R})}if(!u.Magic&&!u.Normal){let T=p.level||0;l.items.push({quality:"hq",code:p.code,item:p,type:u,level:T,name:g+" [Superior]",searchable:[g,"Superior",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" "),tooltip:["Code: "+p.code,"Level: "+T,"Keywords: "+[g,"Superior",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" ")].join(`
`),use:!1,func:R})}if(!u.Magic){let T=p.level||0;l.items.push({quality:"normal",code:p.code,item:p,type:u,level:T,name:g+" [Normal]",searchable:[g,"Normal",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" "),tooltip:["Code: "+p.code,"Level: "+T,"Keywords: "+[g,"Normal",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" ")].join(`
`),use:!1,func:R})}if(!u.Magic&&!u.Normal){let T=p.level||0;l.items.push({quality:"low",code:p.code,item:p,type:u,level:T,name:g+" [Low Quality]",searchable:[g,"Low Quality",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" "),tooltip:["Code: "+p.code,"Level: "+T,"Keywords: "+[g,"Low Quality",p.code,...f(u.Code),C?"exceptional":"nonexceptional",S?"elite":"nonelite"].join(" ")].join(`
`),use:!1,func:R})}}});let Ie=!1,J=window.location.hash.slice(1),re=0;if(J.length){let p=t(J);for(Ie=!0,l.parammap.forEach(u=>{l.params[u.key]=p["get"+u.type+u.size*8](re),re+=u.size});re<p.byteLength;re+=2){let u=p.getUint16(re);l.items[u].use=!0}}return l.visible=!0,_a(l.params,()=>{l.params.group>l.params.players&&(l.params.group=l.params.players),l.params.minilvl>l.params.maxilvl&&(l.params.maxilvl=l.params.minilvl),m()},{deep:!0}),Ie&&V(),(p,u)=>(de(),he("div",null,[Q(l).visible?(de(),he(be,{key:1},[G("div",_Ta,[G("div",VTa,[G("label",null,"Magic Find: "+Te(Q(l).params.mf)+"%",1),ea(G("input",{type:"range",class:"form-range form-range-sm",min:"0",max:"1167","onUpdate:modelValue":u[0]||(u[0]=g=>Q(l).params.mf=g)},null,512),[[ha,Q(l).params.mf,void 0,{number:!0}]])]),G("div",JTa,[G("label",null,"Players in Game: "+Te(Q(l).params.players),1),ea(G("input",{type:"range",class:"form-range form-range-sm",min:"1",max:"8","onUpdate:modelValue":u[1]||(u[1]=g=>Q(l).params.players=g)},null,512),[[ha,Q(l).params.players,void 0,{number:!0}]])]),G("div",QTa,[G("label",null,"Players in Group: "+Te(Q(l).params.group),1),ea(G("input",{type:"range",class:"form-range form-range-sm",min:"1",max:Q(l).params.players,"onUpdate:modelValue":u[2]||(u[2]=g=>Q(l).params.group=g)},null,8,KTa),[[ha,Q(l).params.group,void 0,{number:!0}]])])]),G("div",YTa,[G("div",XTa,[G("label",null,"Minimum ilvl: "+Te(Q(l).params.minilvl),1),ea(G("input",{type:"range",class:"form-range form-range-sm",min:"0",max:110,"onUpdate:modelValue":u[3]||(u[3]=g=>Q(l).params.minilvl=g)},null,512),[[ha,Q(l).params.minilvl,void 0,{number:!0}]])]),G("div",$Ta,[G("label",null,"Max ilvl: "+Te(Q(l).params.maxilvl),1),ea(G("input",{type:"range",class:"form-range form-range-sm",min:Q(l).params.minilvl,max:"110","onUpdate:modelValue":u[4]||(u[4]=g=>Q(l).params.maxilvl=g)},null,8,ZTa),[[ha,Q(l).params.maxilvl,void 0,{number:!0}]])]),G("div",{class:"col-12 col-lg-auto d-flex align-items-center"},[G("button",{class:"btn btn-primary",onClick:V},"Do It!")])]),G("div",e9a,[G("div",a9a,[G("div",r9a,[i9a,ea(G("input",{type:"search",class:"form-control",placeholder:"Search for an item or item code...","onUpdate:modelValue":u[5]||(u[5]=g=>Q(l).itemSearch=g)},null,512),[[ha,Q(l).itemSearch]])]),(de(!0),he(be,null,Ar(Q(l).items,(g,C)=>(de(),he("div",{key:C},[g.use||L(Q(l).itemSearch,g.searchable)?(de(),he("div",{key:0,class:"form-check",title:g.tooltip},[ea(G("input",{type:"checkbox",class:"form-check-input",onChange:m,"onUpdate:modelValue":S=>g.use=S},null,40,l9a),[[ho,g.use]]),G("label",t9a,Te(g.name),1)],8,n9a)):Fa("",!0)]))),128))]),G("div",o9a,[Q(l).calculating?(de(),he("h4",g9a,"Calculating: "+Te((Q(l).progress*100).toFixed(0))+"%",1)):(de(),he("div",s9a,[Q(l).visible?(de(),he("table",c9a,[m9a,G("tbody",null,[(de(!0),he(be,null,Ar(Q(l).areaResults,(g,C)=>(de(),he("tr",{title:g.tooltip,key:C},[G("td",d9a,Te(g.name),1),G("td",u9a,"1:"+Te(h(g.chance)),1)],8,p9a))),128))])])):Fa("",!0)]))]),G("div",M9a,[Q(l).calculating?Fa("",!0):(de(),he("div",h9a,[Q(l).visible?(de(),he("table",v9a,[H9a,G("tbody",null,[(de(!0),he(be,null,Ar(Q(l).packResults,(g,C)=>(de(),he("tr",{title:g.tooltip,key:C},[G("td",{class:"text-left fw-bold",style:ar({color:g.color})},Te(g.name),5),G("td",A9a,"1:"+Te(h(g.chance)),1)],8,b9a))),128))])])):Fa("",!0)]))])])],64)):(de(),he("p",jTa,"Loading..."))]))}};Ao(x9a).mount("#app");
# coding: utf8
import md5
import sys
import re

TEMPLATE = '''
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">

    <style>

    /* Space out content a bit */
    body {
      padding-top: 20px;
      padding-bottom: 20px;
    }

    /* Custom page header */
    .header {
      padding-bottom: 20px;
      padding-right: 15px;
      padding-left: 15px;
      border-bottom: 1px solid #e5e5e5;
    }

    /* Make the masthead heading the same height as the navigation */
    .header h3 {
      margin-top: 0;
      margin-bottom: 0;
      line-height: 40px;
    }

    /* Customize container */
    .container {
        width: auto;
    }
    
    .d3-flame-graph rect {
  stroke: #EEEEEE;
  fill-opacity: .8;
}

.d3-flame-graph rect:hover {
  stroke: #474747;
  stroke-width: 0.5;
  cursor: pointer;
}

.d3-flame-graph-label {
  pointer-events: none;
  white-space: nowrap;
  text-overflow: ellipsis;
  overflow: hidden;
  font-size: 12px;
  font-family: Verdana;
  margin-left: 4px;
  margin-right: 4px;
  line-height: 1.5;
  padding: 0 0 0;
  font-weight: 400;
  color: black;
  text-align: left;
}

.d3-flame-graph .fade {
  opacity: 0.6 !important;
}

.d3-flame-graph .title {
  font-size: 20px;
  font-family: Verdana;
}

.d3-flame-graph-tip {
  line-height: 1;
  font-family: Verdana;
  font-size: 12px;
  padding: 12px;
  background: rgba(0, 0, 0, 0.8);
  color: #fff;
  border-radius: 2px;
  pointer-events: none;
}

/* Creates a small triangle extender for the tooltip */
.d3-flame-graph-tip:after {
  box-sizing: border-box;
  display: inline;
  font-size: 10px;
  width: 100%;
  line-height: 1;
  color: rgba(0, 0, 0, 0.8);
  position: absolute;
  pointer-events: none;
}

/* Northward tooltips */
.d3-flame-graph-tip.n:after {
  content: "\25BC";
  margin: -1px 0 0 0;
  top: 100%;
  left: 0;
  text-align: center;
}

/* Eastward tooltips */
.d3-flame-graph-tip.e:after {
  content: "\25C0";
  margin: -4px 0 0 0;
  top: 50%;
  left: -8px;
}

/* Southward tooltips */
.d3-flame-graph-tip.s:after {
  content: "\25B2";
  margin: 0 0 1px 0;
  top: -8px;
  left: 0;
  text-align: center;
}

/* Westward tooltips */
.d3-flame-graph-tip.w:after {
  content: "\25B6";
  margin: -4px 0 0 -1px;
  top: 50%;
  left: 100%;
}
    </style>

    <title>d3-flame-graph</title>

    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>
  <body>
    <div class="container">
      <div class="header clearfix">
        <nav>
          <div class="pull-right">
            <form class="form-inline" id="form">
              <a class="btn" href="javascript: resetZoom();">Reset zoom</a>
              <a class="btn" href="javascript: clear();">Clear</a>
              <div class="form-group">
                <input type="text" class="form-control" id="term">
              </div>
              <a class="btn btn-primary" href="javascript: search();">Search</a>
            </form>
          </div>
        </nav>
        <h3 class="text-muted">d3-flame-graph</h3>
      </div>
      {modules_div}
      <div id="chart">
      </div>
      <hr>
      <div id="details">
      </div>
      <div>
      <pre>
      
      
      
      
      
      
      
      
      
      
      
      
      </pre>
      </div>
    </div>

    <!-- D3.js -->
    <script src="https://d3js.org/d3.v4.min.js" charset="utf-8"></script>
    
    <!-- d3-tip -->
    <script type="text/javascript" src=https://cdnjs.cloudflare.com/ajax/libs/d3-tip/0.9.1/d3-tip.min.js></script>

    <script>
    !function(t,n){"object"==typeof exports&&"undefined"!=typeof module?n(exports,require("d3")):"function"==typeof define&&define.amd?define(["exports","d3"],n):n(t.d3=t.d3||{},t.d3)}(this,function(t,n){"use strict";n=n&&n.hasOwnProperty("default")?n.default:n;var e="http://www.w3.org/1999/xhtml",r={svg:"http://www.w3.org/2000/svg",xhtml:e,xlink:"http://www.w3.org/1999/xlink",xml:"http://www.w3.org/XML/1998/namespace",xmlns:"http://www.w3.org/2000/xmlns/"},i=function(t){var n=t+="",e=n.indexOf(":");return e>=0&&"xmlns"!==(n=t.slice(0,e))&&(t=t.slice(e+1)),r.hasOwnProperty(n)?{space:r[n],local:t}:t};var a=function(t){var n=i(t);return(n.local?function(t){return function(){return this.ownerDocument.createElementNS(t.space,t.local)}}:function(t){return function(){var n=this.ownerDocument,r=this.namespaceURI;return r===e&&n.documentElement.namespaceURI===e?n.createElement(t):n.createElementNS(r,t)}})(n)},o=function(t){return function(){return this.matches(t)}};if("undefined"!=typeof document){var u=document.documentElement;if(!u.matches){var c=u.webkitMatchesSelector||u.msMatchesSelector||u.mozMatchesSelector||u.oMatchesSelector;o=function(t){return function(){return c.call(this,t)}}}}var f=o,l={};"undefined"!=typeof document&&("onmouseenter"in document.documentElement||(l={mouseenter:"mouseover",mouseleave:"mouseout"}));function s(t,n,e){return t=h(t,n,e),function(n){var e=n.relatedTarget;e&&(e===this||8&e.compareDocumentPosition(this))||t.call(this,n)}}function h(t,n,e){return function(r){try{t.call(this,this.__data__,n,e)}finally{}}}function d(t){return function(){var n=this.__on;if(n){for(var e,r=0,i=-1,a=n.length;r<a;++r)e=n[r],t.type&&e.type!==t.type||e.name!==t.name?n[++i]=e:this.removeEventListener(e.type,e.listener,e.capture);++i?n.length=i:delete this.__on}}}function p(t,n,e){var r=l.hasOwnProperty(t.type)?s:h;return function(i,a,o){var u,c=this.__on,f=r(n,a,o);if(c)for(var l=0,s=c.length;l<s;++l)if((u=c[l]).type===t.type&&u.name===t.name)return this.removeEventListener(u.type,u.listener,u.capture),this.addEventListener(u.type,u.listener=f,u.capture=e),void(u.value=n);this.addEventListener(t.type,f,e),u={type:t.type,name:t.name,value:n,listener:f,capture:e},c?c.push(u):this.__on=[u]}}function g(){}var b=function(t){return null==t?g:function(){return this.querySelector(t)}};function v(){return[]}var y=function(t){return null==t?v:function(){return this.querySelectorAll(t)}},m=function(t){return new Array(t.length)};function w(t,n){this.ownerDocument=t.ownerDocument,this.namespaceURI=t.namespaceURI,this._next=null,this._parent=t,this.__data__=n}w.prototype={constructor:w,appendChild:function(t){return this._parent.insertBefore(t,this._next)},insertBefore:function(t,n){return this._parent.insertBefore(t,n)},querySelector:function(t){return this._parent.querySelector(t)},querySelectorAll:function(t){return this._parent.querySelectorAll(t)}};var _="$";function M(t,n,e,r,i,a){for(var o,u=0,c=n.length,f=a.length;u<f;++u)(o=n[u])?(o.__data__=a[u],r[u]=o):e[u]=new w(t,a[u]);for(;u<c;++u)(o=n[u])&&(i[u]=o)}function x(t,n,e,r,i,a,o){var u,c,f,l={},s=n.length,h=a.length,d=new Array(s);for(u=0;u<s;++u)(c=n[u])&&(d[u]=f=_+o.call(c,c.__data__,u,n),f in l?i[u]=c:l[f]=c);for(u=0;u<h;++u)(c=l[f=_+o.call(t,a[u],u,a)])?(r[u]=c,c.__data__=a[u],l[f]=null):e[u]=new w(t,a[u]);for(u=0;u<s;++u)(c=n[u])&&l[d[u]]===c&&(i[u]=c)}function T(t,n){return t<n?-1:t>n?1:t>=n?0:NaN}var A=function(t){return t.ownerDocument&&t.ownerDocument.defaultView||t.document&&t||t.defaultView};function C(t,n){return t.style.getPropertyValue(n)||A(t).getComputedStyle(t,null).getPropertyValue(n)}function N(t){return t.trim().split(/^|\s+/)}function S(t){return t.classList||new k(t)}function k(t){this._node=t,this._names=N(t.getAttribute("class")||"")}function E(t,n){for(var e=S(t),r=-1,i=n.length;++r<i;)e.add(n[r])}function U(t,n){for(var e=S(t),r=-1,i=n.length;++r<i;)e.remove(n[r])}k.prototype={add:function(t){this._names.indexOf(t)<0&&(this._names.push(t),this._node.setAttribute("class",this._names.join(" ")))},remove:function(t){var n=this._names.indexOf(t);n>=0&&(this._names.splice(n,1),this._node.setAttribute("class",this._names.join(" ")))},contains:function(t){return this._names.indexOf(t)>=0}};function D(){this.textContent=""}function H(){this.innerHTML=""}function F(){this.nextSibling&&this.parentNode.appendChild(this)}function Y(){this.previousSibling&&this.parentNode.insertBefore(this,this.parentNode.firstChild)}function L(){return null}function P(){var t=this.parentNode;t&&t.removeChild(this)}function O(t,n,e){var r=A(t),i=r.CustomEvent;"function"==typeof i?i=new i(n,e):(i=r.document.createEvent("Event"),e?(i.initEvent(n,e.bubbles,e.cancelable),i.detail=e.detail):i.initEvent(n,!1,!1)),t.dispatchEvent(i)}var q=[null];function j(t,n){this._groups=t,this._parents=n}function X(){return new j([[document.documentElement]],q)}j.prototype=X.prototype={constructor:j,select:function(t){"function"!=typeof t&&(t=b(t));for(var n=this._groups,e=n.length,r=new Array(e),i=0;i<e;++i)for(var a,o,u=n[i],c=u.length,f=r[i]=new Array(c),l=0;l<c;++l)(a=u[l])&&(o=t.call(a,a.__data__,l,u))&&("__data__"in a&&(o.__data__=a.__data__),f[l]=o);return new j(r,this._parents)},selectAll:function(t){"function"!=typeof t&&(t=y(t));for(var n=this._groups,e=n.length,r=[],i=[],a=0;a<e;++a)for(var o,u=n[a],c=u.length,f=0;f<c;++f)(o=u[f])&&(r.push(t.call(o,o.__data__,f,u)),i.push(o));return new j(r,i)},filter:function(t){"function"!=typeof t&&(t=f(t));for(var n=this._groups,e=n.length,r=new Array(e),i=0;i<e;++i)for(var a,o=n[i],u=o.length,c=r[i]=[],l=0;l<u;++l)(a=o[l])&&t.call(a,a.__data__,l,o)&&c.push(a);return new j(r,this._parents)},data:function(t,n){if(!t)return p=new Array(this.size()),l=-1,this.each(function(t){p[++l]=t}),p;var e,r=n?x:M,i=this._parents,a=this._groups;"function"!=typeof t&&(e=t,t=function(){return e});for(var o=a.length,u=new Array(o),c=new Array(o),f=new Array(o),l=0;l<o;++l){var s=i[l],h=a[l],d=h.length,p=t.call(s,s&&s.__data__,l,i),g=p.length,b=c[l]=new Array(g),v=u[l]=new Array(g);r(s,h,b,v,f[l]=new Array(d),p,n);for(var y,m,w=0,_=0;w<g;++w)if(y=b[w]){for(w>=_&&(_=w+1);!(m=v[_])&&++_<g;);y._next=m||null}}return(u=new j(u,i))._enter=c,u._exit=f,u},enter:function(){return new j(this._enter||this._groups.map(m),this._parents)},exit:function(){return new j(this._exit||this._groups.map(m),this._parents)},merge:function(t){for(var n=this._groups,e=t._groups,r=n.length,i=e.length,a=Math.min(r,i),o=new Array(r),u=0;u<a;++u)for(var c,f=n[u],l=e[u],s=f.length,h=o[u]=new Array(s),d=0;d<s;++d)(c=f[d]||l[d])&&(h[d]=c);for(;u<r;++u)o[u]=n[u];return new j(o,this._parents)},order:function(){for(var t=this._groups,n=-1,e=t.length;++n<e;)for(var r,i=t[n],a=i.length-1,o=i[a];--a>=0;)(r=i[a])&&(o&&o!==r.nextSibling&&o.parentNode.insertBefore(r,o),o=r);return this},sort:function(t){function n(n,e){return n&&e?t(n.__data__,e.__data__):!n-!e}t||(t=T);for(var e=this._groups,r=e.length,i=new Array(r),a=0;a<r;++a){for(var o,u=e[a],c=u.length,f=i[a]=new Array(c),l=0;l<c;++l)(o=u[l])&&(f[l]=o);f.sort(n)}return new j(i,this._parents).order()},call:function(){var t=arguments[0];return arguments[0]=this,t.apply(null,arguments),this},nodes:function(){var t=new Array(this.size()),n=-1;return this.each(function(){t[++n]=this}),t},node:function(){for(var t=this._groups,n=0,e=t.length;n<e;++n)for(var r=t[n],i=0,a=r.length;i<a;++i){var o=r[i];if(o)return o}return null},size:function(){var t=0;return this.each(function(){++t}),t},empty:function(){return!this.node()},each:function(t){for(var n=this._groups,e=0,r=n.length;e<r;++e)for(var i,a=n[e],o=0,u=a.length;o<u;++o)(i=a[o])&&t.call(i,i.__data__,o,a);return this},attr:function(t,n){var e=i(t);if(arguments.length<2){var r=this.node();return e.local?r.getAttributeNS(e.space,e.local):r.getAttribute(e)}return this.each((null==n?e.local?function(t){return function(){this.removeAttributeNS(t.space,t.local)}}:function(t){return function(){this.removeAttribute(t)}}:"function"==typeof n?e.local?function(t,n){return function(){var e=n.apply(this,arguments);null==e?this.removeAttributeNS(t.space,t.local):this.setAttributeNS(t.space,t.local,e)}}:function(t,n){return function(){var e=n.apply(this,arguments);null==e?this.removeAttribute(t):this.setAttribute(t,e)}}:e.local?function(t,n){return function(){this.setAttributeNS(t.space,t.local,n)}}:function(t,n){return function(){this.setAttribute(t,n)}})(e,n))},style:function(t,n,e){return arguments.length>1?this.each((null==n?function(t){return function(){this.style.removeProperty(t)}}:"function"==typeof n?function(t,n,e){return function(){var r=n.apply(this,arguments);null==r?this.style.removeProperty(t):this.style.setProperty(t,r,e)}}:function(t,n,e){return function(){this.style.setProperty(t,n,e)}})(t,n,null==e?"":e)):C(this.node(),t)},property:function(t,n){return arguments.length>1?this.each((null==n?function(t){return function(){delete this[t]}}:"function"==typeof n?function(t,n){return function(){var e=n.apply(this,arguments);null==e?delete this[t]:this[t]=e}}:function(t,n){return function(){this[t]=n}})(t,n)):this.node()[t]},classed:function(t,n){var e=N(t+"");if(arguments.length<2){for(var r=S(this.node()),i=-1,a=e.length;++i<a;)if(!r.contains(e[i]))return!1;return!0}return this.each(("function"==typeof n?function(t,n){return function(){(n.apply(this,arguments)?E:U)(this,t)}}:n?function(t){return function(){E(this,t)}}:function(t){return function(){U(this,t)}})(e,n))},text:function(t){return arguments.length?this.each(null==t?D:("function"==typeof t?function(t){return function(){var n=t.apply(this,arguments);this.textContent=null==n?"":n}}:function(t){return function(){this.textContent=t}})(t)):this.node().textContent},html:function(t){return arguments.length?this.each(null==t?H:("function"==typeof t?function(t){return function(){var n=t.apply(this,arguments);this.innerHTML=null==n?"":n}}:function(t){return function(){this.innerHTML=t}})(t)):this.node().innerHTML},raise:function(){return this.each(F)},lower:function(){return this.each(Y)},append:function(t){var n="function"==typeof t?t:a(t);return this.select(function(){return this.appendChild(n.apply(this,arguments))})},insert:function(t,n){var e="function"==typeof t?t:a(t),r=null==n?L:"function"==typeof n?n:b(n);return this.select(function(){return this.insertBefore(e.apply(this,arguments),r.apply(this,arguments)||null)})},remove:function(){return this.each(P)},datum:function(t){return arguments.length?this.property("__data__",t):this.node().__data__},on:function(t,n,e){var r,i,a=function(t){return t.trim().split(/^|\s+/).map(function(t){var n="",e=t.indexOf(".");return e>=0&&(n=t.slice(e+1),t=t.slice(0,e)),{type:t,name:n}})}(t+""),o=a.length;if(!(arguments.length<2)){for(u=n?p:d,null==e&&(e=!1),r=0;r<o;++r)this.each(u(a[r],n,e));return this}var u=this.node().__on;if(u)for(var c,f=0,l=u.length;f<l;++f)for(r=0,c=u[f];r<o;++r)if((i=a[r]).type===c.type&&i.name===c.name)return c.value},dispatch:function(t,n){return this.each(("function"==typeof n?function(t,n){return function(){return O(this,t,n.apply(this,arguments))}}:function(t,n){return function(){return O(this,t,n)}})(t,n))}};var z,I=function(t){return"string"==typeof t?new j([[document.querySelector(t)]],[document.documentElement]):new j([[t]],q)},$=function(t,n){if((e=(t=n?t.toExponential(n-1):t.toExponential()).indexOf("e"))<0)return null;var e,r=t.slice(0,e);return[r.length>1?r[0]+r.slice(2):r,+t.slice(e+1)]},B=function(t){return(t=$(Math.abs(t)))?t[1]:NaN},W=function(t,n){var e=$(t,n);if(!e)return t+"";var r=e[0],i=e[1];return i<0?"0."+new Array(-i).join("0")+r:r.length>i+1?r.slice(0,i+1)+"."+r.slice(i+1):r+new Array(i-r.length+2).join("0")},R={"":function(t,n){t=t.toPrecision(n);t:for(var e,r=t.length,i=1,a=-1;i<r;++i)switch(t[i]){case".":a=e=i;break;case"0":0===a&&(a=i),e=i;break;case"e":break t;default:a>0&&(a=0)}return a>0?t.slice(0,a)+t.slice(e+1):t},"%":function(t,n){return(100*t).toFixed(n)},b:function(t){return Math.round(t).toString(2)},c:function(t){return t+""},d:function(t){return Math.round(t).toString(10)},e:function(t,n){return t.toExponential(n)},f:function(t,n){return t.toFixed(n)},g:function(t,n){return t.toPrecision(n)},o:function(t){return Math.round(t).toString(8)},p:function(t,n){return W(100*t,n)},r:W,s:function(t,n){var e=$(t,n);if(!e)return t+"";var r=e[0],i=e[1],a=i-(z=3*Math.max(-8,Math.min(8,Math.floor(i/3))))+1,o=r.length;return a===o?r:a>o?r+new Array(a-o+1).join("0"):a>0?r.slice(0,a)+"."+r.slice(a):"0."+new Array(1-a).join("0")+$(t,Math.max(0,n+a-1))[0]},X:function(t){return Math.round(t).toString(16).toUpperCase()},x:function(t){return Math.round(t).toString(16)}},Z=/^(?:(.)?([<>=^]))?([+\-\( ])?([$#])?(0)?(\d+)?(,)?(\.\d+)?([a-z%])?$/i;function V(t){return new J(t)}function J(t){if(!(n=Z.exec(t)))throw new Error("invalid format: "+t);var n,e=n[1]||" ",r=n[2]||">",i=n[3]||"-",a=n[4]||"",o=!!n[5],u=n[6]&&+n[6],c=!!n[7],f=n[8]&&+n[8].slice(1),l=n[9]||"";"n"===l?(c=!0,l="g"):R[l]||(l=""),(o||"0"===e&&"="===r)&&(o=!0,e="0",r="="),this.fill=e,this.align=r,this.sign=i,this.symbol=a,this.zero=o,this.width=u,this.comma=c,this.precision=f,this.type=l}V.prototype=J.prototype,J.prototype.toString=function(){return this.fill+this.align+this.sign+this.symbol+(this.zero?"0":"")+(null==this.width?"":Math.max(1,0|this.width))+(this.comma?",":"")+(null==this.precision?"":"."+Math.max(0,0|this.precision))+this.type};var G,K,Q,tt=function(t){return t},nt=["y","z","a","f","p","n","µ","m","","k","M","G","T","P","E","Z","Y"];G=function(t){var n,e,r=t.grouping&&t.thousands?(n=t.grouping,e=t.thousands,function(t,r){for(var i=t.length,a=[],o=0,u=n[0],c=0;i>0&&u>0&&(c+u+1>r&&(u=Math.max(1,r-c)),a.push(t.substring(i-=u,i+u)),!((c+=u+1)>r));)u=n[o=(o+1)%n.length];return a.reverse().join(e)}):tt,i=t.currency,a=t.decimal,o=t.numerals?function(t){return function(n){return n.replace(/[0-9]/g,function(n){return t[+n]})}}(t.numerals):tt,u=t.percent||"%";function c(t){var n=(t=V(t)).fill,e=t.align,c=t.sign,f=t.symbol,l=t.zero,s=t.width,h=t.comma,d=t.precision,p=t.type,g="$"===f?i[0]:"#"===f&&/[boxX]/.test(p)?"0"+p.toLowerCase():"",b="$"===f?i[1]:/[%p]/.test(p)?u:"",v=R[p],y=!p||/[defgprs%]/.test(p);function m(t){var i,u,f,m=g,w=b;if("c"===p)w=v(t)+w,t="";else{var _=(t=+t)<0;if(t=v(Math.abs(t),d),_&&0==+t&&(_=!1),m=(_?"("===c?c:"-":"-"===c||"("===c?"":c)+m,w=w+("s"===p?nt[8+z/3]:"")+(_&&"("===c?")":""),y)for(i=-1,u=t.length;++i<u;)if(48>(f=t.charCodeAt(i))||f>57){w=(46===f?a+t.slice(i+1):t.slice(i))+w,t=t.slice(0,i);break}}h&&!l&&(t=r(t,1/0));var M=m.length+t.length+w.length,x=M<s?new Array(s-M+1).join(n):"";switch(h&&l&&(t=r(x+t,x.length?s-w.length:1/0),x=""),e){case"<":t=m+t+w+x;break;case"=":t=m+x+t+w;break;case"^":t=x.slice(0,M=x.length>>1)+m+t+w+x.slice(M);break;default:t=x+m+t+w}return o(t)}return d=null==d?p?6:12:/[gprs]/.test(p)?Math.max(1,Math.min(21,d)):Math.max(0,Math.min(20,d)),m.toString=function(){return t+""},m}return{format:c,formatPrefix:function(t,n){var e=c(((t=V(t)).type="f",t)),r=3*Math.max(-8,Math.min(8,Math.floor(B(n)/3))),i=Math.pow(10,-r),a=nt[8+r/3];return function(t){return e(i*t)+a}}}}({decimal:".",thousands:",",grouping:[3],currency:["$",""]}),K=G.format,Q=G.formatPrefix;var et=function(t,n){return t<n?-1:t>n?1:t>=n?0:NaN};var rt,it,at=(1===(rt=et).length&&(it=rt,rt=function(t,n){return et(it(t),n)}),{left:function(t,n,e,r){for(null==e&&(e=0),null==r&&(r=t.length);e<r;){var i=e+r>>>1;rt(t[i],n)<0?e=i+1:r=i}return e},right:function(t,n,e,r){for(null==e&&(e=0),null==r&&(r=t.length);e<r;){var i=e+r>>>1;rt(t[i],n)>0?r=i:e=i+1}return e}}).right,ot=Math.sqrt(50),ut=Math.sqrt(10),ct=Math.sqrt(2),ft=function(t,n,e){var r,i,a,o=n<t,u=-1;if(o&&(r=t,t=n,n=r),0===(a=lt(t,n,e))||!isFinite(a))return[];if(a>0)for(t=Math.ceil(t/a),n=Math.floor(n/a),i=new Array(r=Math.ceil(n-t+1));++u<r;)i[u]=(t+u)*a;else for(t=Math.floor(t*a),n=Math.ceil(n*a),i=new Array(r=Math.ceil(t-n+1));++u<r;)i[u]=(t-u)/a;return o&&i.reverse(),i};function lt(t,n,e){var r=(n-t)/Math.max(0,e),i=Math.floor(Math.log(r)/Math.LN10),a=r/Math.pow(10,i);return i>=0?(a>=ot?10:a>=ut?5:a>=ct?2:1)*Math.pow(10,i):-Math.pow(10,-i)/(a>=ot?10:a>=ut?5:a>=ct?2:1)}function st(t){var n=0,e=t.children,r=e&&e.length;if(r)for(;--r>=0;)n+=e[r].value;else n=1;t.value=n}function ht(t,n){var e,r,i,a,o,u=new bt(t),c=+t.value&&(u.value=t.value),f=[u];for(null==n&&(n=dt);e=f.pop();)if(c&&(e.value=+e.data.value),(i=n(e.data))&&(o=i.length))for(e.children=new Array(o),a=o-1;a>=0;--a)f.push(r=e.children[a]=new bt(i[a])),r.parent=e,r.depth=e.depth+1;return u.eachBefore(gt)}function dt(t){return t.children}function pt(t){t.data=t.data.data}function gt(t){var n=0;do{t.height=n}while((t=t.parent)&&t.height<++n)}function bt(t){this.data=t,this.depth=this.height=0,this.parent=null}bt.prototype=ht.prototype={constructor:bt,count:function(){return this.eachAfter(st)},each:function(t){var n,e,r,i,a=this,o=[a];do{for(n=o.reverse(),o=[];a=n.pop();)if(t(a),e=a.children)for(r=0,i=e.length;r<i;++r)o.push(e[r])}while(o.length);return this},eachAfter:function(t){for(var n,e,r,i=this,a=[i],o=[];i=a.pop();)if(o.push(i),n=i.children)for(e=0,r=n.length;e<r;++e)a.push(n[e]);for(;i=o.pop();)t(i);return this},eachBefore:function(t){for(var n,e,r=this,i=[r];r=i.pop();)if(t(r),n=r.children)for(e=n.length-1;e>=0;--e)i.push(n[e]);return this},sum:function(t){return this.eachAfter(function(n){for(var e=+t(n.data)||0,r=n.children,i=r&&r.length;--i>=0;)e+=r[i].value;n.value=e})},sort:function(t){return this.eachBefore(function(n){n.children&&n.children.sort(t)})},path:function(t){for(var n=this,e=function(t,n){if(t===n)return t;var e=t.ancestors(),r=n.ancestors(),i=null;for(t=e.pop(),n=r.pop();t===n;)i=t,t=e.pop(),n=r.pop();return i}(n,t),r=[n];n!==e;)n=n.parent,r.push(n);for(var i=r.length;t!==e;)r.splice(i,0,t),t=t.parent;return r},ancestors:function(){for(var t=this,n=[t];t=t.parent;)n.push(t);return n},descendants:function(){var t=[];return this.each(function(n){t.push(n)}),t},leaves:function(){var t=[];return this.eachBefore(function(n){n.children||t.push(n)}),t},links:function(){var t=this,n=[];return t.each(function(e){e!==t&&n.push({source:e.parent,target:e})}),n},copy:function(){return ht(this).eachBefore(pt)}};var vt=function(t){t.x0=Math.round(t.x0),t.y0=Math.round(t.y0),t.x1=Math.round(t.x1),t.y1=Math.round(t.y1)},yt=function(t,n,e,r,i){for(var a,o=t.children,u=-1,c=o.length,f=t.value&&(r-n)/t.value;++u<c;)(a=o[u]).y0=e,a.y1=i,a.x0=n,a.x1=n+=a.value*f},mt=function(){var t=1,n=1,e=0,r=!1;function i(i){var a=i.height+1;return i.x0=i.y0=e,i.x1=t,i.y1=n/a,i.eachBefore(function(t,n){return function(r){r.children&&yt(r,r.x0,t*(r.depth+1)/n,r.x1,t*(r.depth+2)/n);var i=r.x0,a=r.y0,o=r.x1-e,u=r.y1-e;o<i&&(i=o=(i+o)/2),u<a&&(a=u=(a+u)/2),r.x0=i,r.y0=a,r.x1=o,r.y1=u}}(n,a)),r&&i.eachBefore(vt),i}return i.round=function(t){return arguments.length?(r=!!t,i):r},i.size=function(e){return arguments.length?(t=+e[0],n=+e[1],i):[t,n]},i.padding=function(t){return arguments.length?(e=+t,i):e},i},wt=Array.prototype,_t=wt.map,Mt=wt.slice,xt=function(t,n,e){t.prototype=n.prototype=e,e.constructor=t};function Tt(t,n){var e=Object.create(t.prototype);for(var r in n)e[r]=n[r];return e}function At(){}var Ct="\\s*([+-]?\\d+)\\s*",Nt="\\s*([+-]?\\d*\\.?\\d+(?:[eE][+-]?\\d+)?)\\s*",St="\\s*([+-]?\\d*\\.?\\d+(?:[eE][+-]?\\d+)?)%\\s*",kt=/^#([0-9a-f]{3})$/,Et=/^#([0-9a-f]{6})$/,Ut=new RegExp("^rgb\\("+[Ct,Ct,Ct]+"\\)$"),Dt=new RegExp("^rgb\\("+[St,St,St]+"\\)$"),Ht=new RegExp("^rgba\\("+[Ct,Ct,Ct,Nt]+"\\)$"),Ft=new RegExp("^rgba\\("+[St,St,St,Nt]+"\\)$"),Yt=new RegExp("^hsl\\("+[Nt,St,St]+"\\)$"),Lt=new RegExp("^hsla\\("+[Nt,St,St,Nt]+"\\)$"),Pt={aliceblue:15792383,antiquewhite:16444375,aqua:65535,aquamarine:8388564,azure:15794175,beige:16119260,bisque:16770244,black:0,blanchedalmond:16772045,blue:255,blueviolet:9055202,brown:10824234,burlywood:14596231,cadetblue:6266528,chartreuse:8388352,chocolate:13789470,coral:16744272,cornflowerblue:6591981,cornsilk:16775388,crimson:14423100,cyan:65535,darkblue:139,darkcyan:35723,darkgoldenrod:12092939,darkgray:11119017,darkgreen:25600,darkgrey:11119017,darkkhaki:12433259,darkmagenta:9109643,darkolivegreen:5597999,darkorange:16747520,darkorchid:10040012,darkred:9109504,darksalmon:15308410,darkseagreen:9419919,darkslateblue:4734347,darkslategray:3100495,darkslategrey:3100495,darkturquoise:52945,darkviolet:9699539,deeppink:16716947,deepskyblue:49151,dimgray:6908265,dimgrey:6908265,dodgerblue:2003199,firebrick:11674146,floralwhite:16775920,forestgreen:2263842,fuchsia:16711935,gainsboro:14474460,ghostwhite:16316671,gold:16766720,goldenrod:14329120,gray:8421504,green:32768,greenyellow:11403055,grey:8421504,honeydew:15794160,hotpink:16738740,indianred:13458524,indigo:4915330,ivory:16777200,khaki:15787660,lavender:15132410,lavenderblush:16773365,lawngreen:8190976,lemonchiffon:16775885,lightblue:11393254,lightcoral:15761536,lightcyan:14745599,lightgoldenrodyellow:16448210,lightgray:13882323,lightgreen:9498256,lightgrey:13882323,lightpink:16758465,lightsalmon:16752762,lightseagreen:2142890,lightskyblue:8900346,lightslategray:7833753,lightslategrey:7833753,lightsteelblue:11584734,lightyellow:16777184,lime:65280,limegreen:3329330,linen:16445670,magenta:16711935,maroon:8388608,mediumaquamarine:6737322,mediumblue:205,mediumorchid:12211667,mediumpurple:9662683,mediumseagreen:3978097,mediumslateblue:8087790,mediumspringgreen:64154,mediumturquoise:4772300,mediumvioletred:13047173,midnightblue:1644912,mintcream:16121850,mistyrose:16770273,moccasin:16770229,navajowhite:16768685,navy:128,oldlace:16643558,olive:8421376,olivedrab:7048739,orange:16753920,orangered:16729344,orchid:14315734,palegoldenrod:15657130,palegreen:10025880,paleturquoise:11529966,palevioletred:14381203,papayawhip:16773077,peachpuff:16767673,peru:13468991,pink:16761035,plum:14524637,powderblue:11591910,purple:8388736,rebeccapurple:6697881,red:16711680,rosybrown:12357519,royalblue:4286945,saddlebrown:9127187,salmon:16416882,sandybrown:16032864,seagreen:3050327,seashell:16774638,sienna:10506797,silver:12632256,skyblue:8900331,slateblue:6970061,slategray:7372944,slategrey:7372944,snow:16775930,springgreen:65407,steelblue:4620980,tan:13808780,teal:32896,thistle:14204888,tomato:16737095,turquoise:4251856,violet:15631086,wheat:16113331,white:16777215,whitesmoke:16119285,yellow:16776960,yellowgreen:10145074};function Ot(t){var n;return t=(t+"").trim().toLowerCase(),(n=kt.exec(t))?new It((n=parseInt(n[1],16))>>8&15|n>>4&240,n>>4&15|240&n,(15&n)<<4|15&n,1):(n=Et.exec(t))?qt(parseInt(n[1],16)):(n=Ut.exec(t))?new It(n[1],n[2],n[3],1):(n=Dt.exec(t))?new It(255*n[1]/100,255*n[2]/100,255*n[3]/100,1):(n=Ht.exec(t))?jt(n[1],n[2],n[3],n[4]):(n=Ft.exec(t))?jt(255*n[1]/100,255*n[2]/100,255*n[3]/100,n[4]):(n=Yt.exec(t))?$t(n[1],n[2]/100,n[3]/100,1):(n=Lt.exec(t))?$t(n[1],n[2]/100,n[3]/100,n[4]):Pt.hasOwnProperty(t)?qt(Pt[t]):"transparent"===t?new It(NaN,NaN,NaN,0):null}function qt(t){return new It(t>>16&255,t>>8&255,255&t,1)}function jt(t,n,e,r){return r<=0&&(t=n=e=NaN),new It(t,n,e,r)}function Xt(t){return t instanceof At||(t=Ot(t)),t?new It((t=t.rgb()).r,t.g,t.b,t.opacity):new It}function zt(t,n,e,r){return 1===arguments.length?Xt(t):new It(t,n,e,null==r?1:r)}function It(t,n,e,r){this.r=+t,this.g=+n,this.b=+e,this.opacity=+r}function $t(t,n,e,r){return r<=0?t=n=e=NaN:e<=0||e>=1?t=n=NaN:n<=0&&(t=NaN),new Bt(t,n,e,r)}function Bt(t,n,e,r){this.h=+t,this.s=+n,this.l=+e,this.opacity=+r}function Wt(t,n,e){return 255*(t<60?n+(e-n)*t/60:t<180?e:t<240?n+(e-n)*(240-t)/60:n)}xt(At,Ot,{displayable:function(){return this.rgb().displayable()},toString:function(){return this.rgb()+""}}),xt(It,zt,Tt(At,{brighter:function(t){return t=null==t?1/.7:Math.pow(1/.7,t),new It(this.r*t,this.g*t,this.b*t,this.opacity)},darker:function(t){return t=null==t?.7:Math.pow(.7,t),new It(this.r*t,this.g*t,this.b*t,this.opacity)},rgb:function(){return this},displayable:function(){return 0<=this.r&&this.r<=255&&0<=this.g&&this.g<=255&&0<=this.b&&this.b<=255&&0<=this.opacity&&this.opacity<=1},toString:function(){var t=this.opacity;return(1===(t=isNaN(t)?1:Math.max(0,Math.min(1,t)))?"rgb(":"rgba(")+Math.max(0,Math.min(255,Math.round(this.r)||0))+", "+Math.max(0,Math.min(255,Math.round(this.g)||0))+", "+Math.max(0,Math.min(255,Math.round(this.b)||0))+(1===t?")":", "+t+")")}})),xt(Bt,function(t,n,e,r){return 1===arguments.length?function(t){if(t instanceof Bt)return new Bt(t.h,t.s,t.l,t.opacity);if(t instanceof At||(t=Ot(t)),!t)return new Bt;if(t instanceof Bt)return t;var n=(t=t.rgb()).r/255,e=t.g/255,r=t.b/255,i=Math.min(n,e,r),a=Math.max(n,e,r),o=NaN,u=a-i,c=(a+i)/2;return u?(o=n===a?(e-r)/u+6*(e<r):e===a?(r-n)/u+2:(n-e)/u+4,u/=c<.5?a+i:2-a-i,o*=60):u=c>0&&c<1?0:o,new Bt(o,u,c,t.opacity)}(t):new Bt(t,n,e,null==r?1:r)},Tt(At,{brighter:function(t){return t=null==t?1/.7:Math.pow(1/.7,t),new Bt(this.h,this.s,this.l*t,this.opacity)},darker:function(t){return t=null==t?.7:Math.pow(.7,t),new Bt(this.h,this.s,this.l*t,this.opacity)},rgb:function(){var t=this.h%360+360*(this.h<0),n=isNaN(t)||isNaN(this.s)?0:this.s,e=this.l,r=e+(e<.5?e:1-e)*n,i=2*e-r;return new It(Wt(t>=240?t-240:t+120,i,r),Wt(t,i,r),Wt(t<120?t+240:t-120,i,r),this.opacity)},displayable:function(){return(0<=this.s&&this.s<=1||isNaN(this.s))&&0<=this.l&&this.l<=1&&0<=this.opacity&&this.opacity<=1}}));var Rt=Math.PI/180,Zt=180/Math.PI,Vt=.95047,Jt=1,Gt=1.08883,Kt=4/29,Qt=6/29,tn=3*Qt*Qt,nn=Qt*Qt*Qt;function en(t){if(t instanceof rn)return new rn(t.l,t.a,t.b,t.opacity);if(t instanceof fn){var n=t.h*Rt;return new rn(t.l,Math.cos(n)*t.c,Math.sin(n)*t.c,t.opacity)}t instanceof It||(t=Xt(t));var e=cn(t.r),r=cn(t.g),i=cn(t.b),a=an((.4124564*e+.3575761*r+.1804375*i)/Vt),o=an((.2126729*e+.7151522*r+.072175*i)/Jt);return new rn(116*o-16,500*(a-o),200*(o-an((.0193339*e+.119192*r+.9503041*i)/Gt)),t.opacity)}function rn(t,n,e,r){this.l=+t,this.a=+n,this.b=+e,this.opacity=+r}function an(t){return t>nn?Math.pow(t,1/3):t/tn+Kt}function on(t){return t>Qt?t*t*t:tn*(t-Kt)}function un(t){return 255*(t<=.0031308?12.92*t:1.055*Math.pow(t,1/2.4)-.055)}function cn(t){return(t/=255)<=.04045?t/12.92:Math.pow((t+.055)/1.055,2.4)}function fn(t,n,e,r){this.h=+t,this.c=+n,this.l=+e,this.opacity=+r}xt(rn,function(t,n,e,r){return 1===arguments.length?en(t):new rn(t,n,e,null==r?1:r)},Tt(At,{brighter:function(t){return new rn(this.l+18*(null==t?1:t),this.a,this.b,this.opacity)},darker:function(t){return new rn(this.l-18*(null==t?1:t),this.a,this.b,this.opacity)},rgb:function(){var t=(this.l+16)/116,n=isNaN(this.a)?t:t+this.a/500,e=isNaN(this.b)?t:t-this.b/200;return t=Jt*on(t),new It(un(3.2404542*(n=Vt*on(n))-1.5371385*t-.4985314*(e=Gt*on(e))),un(-.969266*n+1.8760108*t+.041556*e),un(.0556434*n-.2040259*t+1.0572252*e),this.opacity)}})),xt(fn,function(t,n,e,r){return 1===arguments.length?function(t){if(t instanceof fn)return new fn(t.h,t.c,t.l,t.opacity);t instanceof rn||(t=en(t));var n=Math.atan2(t.b,t.a)*Zt;return new fn(n<0?n+360:n,Math.sqrt(t.a*t.a+t.b*t.b),t.l,t.opacity)}(t):new fn(t,n,e,null==r?1:r)},Tt(At,{brighter:function(t){return new fn(this.h,this.c,this.l+18*(null==t?1:t),this.opacity)},darker:function(t){return new fn(this.h,this.c,this.l-18*(null==t?1:t),this.opacity)},rgb:function(){return en(this).rgb()}}));var ln=-.14861,sn=1.78277,hn=-.29227,dn=-.90649,pn=1.97294,gn=pn*dn,bn=pn*sn,vn=sn*hn-dn*ln;function yn(t,n,e,r){return 1===arguments.length?function(t){if(t instanceof mn)return new mn(t.h,t.s,t.l,t.opacity);t instanceof It||(t=Xt(t));var n=t.r/255,e=t.g/255,r=t.b/255,i=(vn*r+gn*n-bn*e)/(vn+gn-bn),a=r-i,o=(pn*(e-i)-hn*a)/dn,u=Math.sqrt(o*o+a*a)/(pn*i*(1-i)),c=u?Math.atan2(o,a)*Zt-120:NaN;return new mn(c<0?c+360:c,u,i,t.opacity)}(t):new mn(t,n,e,null==r?1:r)}function mn(t,n,e,r){this.h=+t,this.s=+n,this.l=+e,this.opacity=+r}xt(mn,yn,Tt(At,{brighter:function(t){return t=null==t?1/.7:Math.pow(1/.7,t),new mn(this.h,this.s,this.l*t,this.opacity)},darker:function(t){return t=null==t?.7:Math.pow(.7,t),new mn(this.h,this.s,this.l*t,this.opacity)},rgb:function(){var t=isNaN(this.h)?0:(this.h+120)*Rt,n=+this.l,e=isNaN(this.s)?0:this.s*n*(1-n),r=Math.cos(t),i=Math.sin(t);return new It(255*(n+e*(ln*r+sn*i)),255*(n+e*(hn*r+dn*i)),255*(n+e*(pn*r)),this.opacity)}}));var wn=function(t){return function(){return t}};function _n(t,n){return function(e){return t+e*n}}function Mn(t){return 1==(t=+t)?xn:function(n,e){return e-n?function(t,n,e){return t=Math.pow(t,e),n=Math.pow(n,e)-t,e=1/e,function(r){return Math.pow(t+r*n,e)}}(n,e,t):wn(isNaN(n)?e:n)}}function xn(t,n){var e=n-t;return e?_n(t,e):wn(isNaN(t)?n:t)}var Tn=function t(n){var e=Mn(n);function r(t,n){var r=e((t=zt(t)).r,(n=zt(n)).r),i=e(t.g,n.g),a=e(t.b,n.b),o=xn(t.opacity,n.opacity);return function(n){return t.r=r(n),t.g=i(n),t.b=a(n),t.opacity=o(n),t+""}}return r.gamma=t,r}(1),An=function(t,n){return n-=t=+t,function(e){return t+n*e}},Cn=/[-+]?(?:\d+\.?\d*|\.?\d+)(?:[eE][-+]?\d+)?/g,Nn=new RegExp(Cn.source,"g");var Sn,kn,En,Un,Dn=function(t,n){var e,r,i,a=Cn.lastIndex=Nn.lastIndex=0,o=-1,u=[],c=[];for(t+="",n+="";(e=Cn.exec(t))&&(r=Nn.exec(n));)(i=r.index)>a&&(i=n.slice(a,i),u[o]?u[o]+=i:u[++o]=i),(e=e[0])===(r=r[0])?u[o]?u[o]+=r:u[++o]=r:(u[++o]=null,c.push({i:o,x:An(e,r)})),a=Nn.lastIndex;return a<n.length&&(i=n.slice(a),u[o]?u[o]+=i:u[++o]=i),u.length<2?c[0]?function(t){return function(n){return t(n)+""}}(c[0].x):function(t){return function(){return t}}(n):(n=c.length,function(t){for(var e,r=0;r<n;++r)u[(e=c[r]).i]=e.x(t);return u.join("")})},Hn=function(t,n){var e,r=typeof n;return null==n||"boolean"===r?wn(n):("number"===r?An:"string"===r?(e=Ot(n))?(n=e,Tn):Dn:n instanceof Ot?Tn:n instanceof Date?function(t,n){var e=new Date;return n-=t=+t,function(r){return e.setTime(t+n*r),e}}:Array.isArray(n)?function(t,n){var e,r=n?n.length:0,i=t?Math.min(r,t.length):0,a=new Array(r),o=new Array(r);for(e=0;e<i;++e)a[e]=Hn(t[e],n[e]);for(;e<r;++e)o[e]=n[e];return function(t){for(e=0;e<i;++e)o[e]=a[e](t);return o}}:"function"!=typeof n.valueOf&&"function"!=typeof n.toString||isNaN(n)?function(t,n){var e,r={},i={};for(e in null!==t&&"object"==typeof t||(t={}),null!==n&&"object"==typeof n||(n={}),n)e in t?r[e]=Hn(t[e],n[e]):i[e]=n[e];return function(t){for(e in r)i[e]=r[e](t);return i}}:An)(t,n)},Fn=function(t,n){return n-=t=+t,function(e){return Math.round(t+n*e)}},Yn=180/Math.PI,Ln={translateX:0,translateY:0,rotate:0,skewX:0,scaleX:1,scaleY:1},Pn=function(t,n,e,r,i,a){var o,u,c;return(o=Math.sqrt(t*t+n*n))&&(t/=o,n/=o),(c=t*e+n*r)&&(e-=t*c,r-=n*c),(u=Math.sqrt(e*e+r*r))&&(e/=u,r/=u,c/=u),t*r<n*e&&(t=-t,n=-n,c=-c,o=-o),{translateX:i,translateY:a,rotate:Math.atan2(n,t)*Yn,skewX:Math.atan(c)*Yn,scaleX:o,scaleY:u}};function On(t,n,e,r){function i(t){return t.length?t.pop()+" ":""}return function(a,o){var u=[],c=[];return a=t(a),o=t(o),function(t,r,i,a,o,u){if(t!==i||r!==a){var c=o.push("translate(",null,n,null,e);u.push({i:c-4,x:An(t,i)},{i:c-2,x:An(r,a)})}else(i||a)&&o.push("translate("+i+n+a+e)}(a.translateX,a.translateY,o.translateX,o.translateY,u,c),function(t,n,e,a){t!==n?(t-n>180?n+=360:n-t>180&&(t+=360),a.push({i:e.push(i(e)+"rotate(",null,r)-2,x:An(t,n)})):n&&e.push(i(e)+"rotate("+n+r)}(a.rotate,o.rotate,u,c),function(t,n,e,a){t!==n?a.push({i:e.push(i(e)+"skewX(",null,r)-2,x:An(t,n)}):n&&e.push(i(e)+"skewX("+n+r)}(a.skewX,o.skewX,u,c),function(t,n,e,r,a,o){if(t!==e||n!==r){var u=a.push(i(a)+"scale(",null,",",null,")");o.push({i:u-4,x:An(t,e)},{i:u-2,x:An(n,r)})}else 1===e&&1===r||a.push(i(a)+"scale("+e+","+r+")")}(a.scaleX,a.scaleY,o.scaleX,o.scaleY,u,c),a=o=null,function(t){for(var n,e=-1,r=c.length;++e<r;)u[(n=c[e]).i]=n.x(t);return u.join("")}}}var qn=On(function(t){return"none"===t?Ln:(Sn||(Sn=document.createElement("DIV"),kn=document.documentElement,En=document.defaultView),Sn.style.transform=t,t=En.getComputedStyle(kn.appendChild(Sn),null).getPropertyValue("transform"),kn.removeChild(Sn),t=t.slice(7,-1).split(","),Pn(+t[0],+t[1],+t[2],+t[3],+t[4],+t[5]))},"px, ","px)","deg)"),jn=On(function(t){return null==t?Ln:(Un||(Un=document.createElementNS("http://www.w3.org/2000/svg","g")),Un.setAttribute("transform",t),(t=Un.transform.baseVal.consolidate())?(t=t.matrix,Pn(t.a,t.b,t.c,t.d,t.e,t.f)):Ln)},", ",")",")");function Xn(t){return function n(e){function r(n,r){var i=t((n=yn(n)).h,(r=yn(r)).h),a=xn(n.s,r.s),o=xn(n.l,r.l),u=xn(n.opacity,r.opacity);return function(t){return n.h=i(t),n.s=a(t),n.l=o(Math.pow(t,e)),n.opacity=u(t),n+""}}return e=+e,r.gamma=n,r}(1)}Xn(function(t,n){var e=n-t;return e?_n(t,e>180||e<-180?e-360*Math.round(e/360):e):wn(isNaN(t)?n:t)});var zn=Xn(xn),In=function(t){return function(){return t}},$n=function(t){return+t},Bn=[0,1];function Wn(t,n){return(n-=t=+t)?function(e){return(e-t)/n}:In(n)}function Rn(t,n,e,r){var i=t[0],a=t[1],o=n[0],u=n[1];return a<i?(i=e(a,i),o=r(u,o)):(i=e(i,a),o=r(o,u)),function(t){return o(i(t))}}function Zn(t,n,e,r){var i=Math.min(t.length,n.length)-1,a=new Array(i),o=new Array(i),u=-1;for(t[i]<t[0]&&(t=t.slice().reverse(),n=n.slice().reverse());++u<i;)a[u]=e(t[u],t[u+1]),o[u]=r(n[u],n[u+1]);return function(n){var e=at(t,n,1,i)-1;return o[e](a[e](n))}}var Vn=function(t,n,e){var r,i=t[0],a=t[t.length-1],o=function(t,n,e){var r=Math.abs(n-t)/Math.max(0,e),i=Math.pow(10,Math.floor(Math.log(r)/Math.LN10)),a=r/i;return a>=ot?i*=10:a>=ut?i*=5:a>=ct&&(i*=2),n<t?-i:i}(i,a,null==n?10:n);switch((e=V(null==e?",f":e)).type){case"s":var u=Math.max(Math.abs(i),Math.abs(a));return null!=e.precision||isNaN(r=function(t,n){return Math.max(0,3*Math.max(-8,Math.min(8,Math.floor(B(n)/3)))-B(Math.abs(t)))}(o,u))||(e.precision=r),Q(e,u);case"":case"e":case"g":case"p":case"r":null!=e.precision||isNaN(r=function(t,n){return t=Math.abs(t),n=Math.abs(n)-t,Math.max(0,B(n)-B(t))+1}(o,Math.max(Math.abs(i),Math.abs(a))))||(e.precision=r-("e"===e.type));break;case"f":case"%":null!=e.precision||isNaN(r=function(t){return Math.max(0,-B(Math.abs(t)))}(o))||(e.precision=r-2*("%"===e.type))}return K(e)};function Jn(){var t=function(t,n){var e,r,i,a=Bn,o=Bn,u=Hn,c=!1;function f(){return e=Math.min(a.length,o.length)>2?Zn:Rn,r=i=null,l}function l(n){return(r||(r=e(a,o,c?function(t){return function(n,e){var r=t(n=+n,e=+e);return function(t){return t<=n?0:t>=e?1:r(t)}}}(t):t,u)))(+n)}return l.invert=function(t){return(i||(i=e(o,a,Wn,c?function(t){return function(n,e){var r=t(n=+n,e=+e);return function(t){return t<=0?n:t>=1?e:r(t)}}}(n):n)))(+t)},l.domain=function(t){return arguments.length?(a=_t.call(t,$n),f()):a.slice()},l.range=function(t){return arguments.length?(o=Mt.call(t),f()):o.slice()},l.rangeRound=function(t){return o=Mt.call(t),u=Fn,f()},l.clamp=function(t){return arguments.length?(c=!!t,f()):c},l.interpolate=function(t){return arguments.length?(u=t,f()):u},f()}(Wn,An);return t.copy=function(){return n=t,Jn().domain(n.domain()).range(n.range()).interpolate(n.interpolate()).clamp(n.clamp());var n},function(t){var n=t.domain;return t.ticks=function(t){var e=n();return ft(e[0],e[e.length-1],null==t?10:t)},t.tickFormat=function(t,e){return Vn(n(),t,e)},t.nice=function(e){null==e&&(e=10);var r,i=n(),a=0,o=i.length-1,u=i[a],c=i[o];return c<u&&(r=u,u=c,c=r,r=a,a=o,o=r),(r=lt(u,c,e))>0?r=lt(u=Math.floor(u/r)*r,c=Math.ceil(c/r)*r,e):r<0&&(r=lt(u=Math.ceil(u*r)/r,c=Math.floor(c*r)/r,e)),r>0?(i[a]=Math.floor(u/r)*r,i[o]=Math.ceil(c/r)*r,n(i)):r<0&&(i[a]=Math.ceil(u*r)/r,i[o]=Math.floor(c*r)/r,n(i)),t},t}(t)}var Gn=new Date,Kn=new Date;function Qn(t,n,e,r){function i(n){return t(n=new Date(+n)),n}return i.floor=i,i.ceil=function(e){return t(e=new Date(e-1)),n(e,1),t(e),e},i.round=function(t){var n=i(t),e=i.ceil(t);return t-n<e-t?n:e},i.offset=function(t,e){return n(t=new Date(+t),null==e?1:Math.floor(e)),t},i.range=function(e,r,a){var o=[];if(e=i.ceil(e),a=null==a?1:Math.floor(a),!(e<r&&a>0))return o;do{o.push(new Date(+e))}while(n(e,a),t(e),e<r);return o},i.filter=function(e){return Qn(function(n){if(n>=n)for(;t(n),!e(n);)n.setTime(n-1)},function(t,r){if(t>=t)if(r<0)for(;++r<=0;)for(;n(t,-1),!e(t););else for(;--r>=0;)for(;n(t,1),!e(t););})},e&&(i.count=function(n,r){return Gn.setTime(+n),Kn.setTime(+r),t(Gn),t(Kn),Math.floor(e(Gn,Kn))},i.every=function(t){return t=Math.floor(t),isFinite(t)&&t>0?t>1?i.filter(r?function(n){return r(n)%t==0}:function(n){return i.count(0,n)%t==0}):i:null}),i}var te=Qn(function(){},function(t,n){t.setTime(+t+n)},function(t,n){return n-t});te.every=function(t){return t=Math.floor(t),isFinite(t)&&t>0?t>1?Qn(function(n){n.setTime(Math.floor(n/t)*t)},function(n,e){n.setTime(+n+e*t)},function(n,e){return(e-n)/t}):te:null};var ne=6e4,ee=6048e5,re=(Qn(function(t){t.setTime(1e3*Math.floor(t/1e3))},function(t,n){t.setTime(+t+1e3*n)},function(t,n){return(n-t)/1e3},function(t){return t.getUTCSeconds()}),Qn(function(t){t.setTime(Math.floor(t/ne)*ne)},function(t,n){t.setTime(+t+n*ne)},function(t,n){return(n-t)/ne},function(t){return t.getMinutes()}),Qn(function(t){var n=t.getTimezoneOffset()*ne%36e5;n<0&&(n+=36e5),t.setTime(36e5*Math.floor((+t-n)/36e5)+n)},function(t,n){t.setTime(+t+36e5*n)},function(t,n){return(n-t)/36e5},function(t){return t.getHours()}),Qn(function(t){t.setHours(0,0,0,0)},function(t,n){t.setDate(t.getDate()+n)},function(t,n){return(n-t-(n.getTimezoneOffset()-t.getTimezoneOffset())*ne)/864e5},function(t){return t.getDate()-1}));function ie(t){return Qn(function(n){n.setDate(n.getDate()-(n.getDay()+7-t)%7),n.setHours(0,0,0,0)},function(t,n){t.setDate(t.getDate()+7*n)},function(t,n){return(n-t-(n.getTimezoneOffset()-t.getTimezoneOffset())*ne)/ee})}var ae=ie(0),oe=ie(1),ue=(ie(2),ie(3),ie(4),ie(5),ie(6),Qn(function(t){t.setDate(1),t.setHours(0,0,0,0)},function(t,n){t.setMonth(t.getMonth()+n)},function(t,n){return n.getMonth()-t.getMonth()+12*(n.getFullYear()-t.getFullYear())},function(t){return t.getMonth()}),Qn(function(t){t.setMonth(0,1),t.setHours(0,0,0,0)},function(t,n){t.setFullYear(t.getFullYear()+n)},function(t,n){return n.getFullYear()-t.getFullYear()},function(t){return t.getFullYear()}));ue.every=function(t){return isFinite(t=Math.floor(t))&&t>0?Qn(function(n){n.setFullYear(Math.floor(n.getFullYear()/t)*t),n.setMonth(0,1),n.setHours(0,0,0,0)},function(n,e){n.setFullYear(n.getFullYear()+e*t)}):null};Qn(function(t){t.setUTCSeconds(0,0)},function(t,n){t.setTime(+t+n*ne)},function(t,n){return(n-t)/ne},function(t){return t.getUTCMinutes()}),Qn(function(t){t.setUTCMinutes(0,0,0)},function(t,n){t.setTime(+t+36e5*n)},function(t,n){return(n-t)/36e5},function(t){return t.getUTCHours()});var ce=Qn(function(t){t.setUTCHours(0,0,0,0)},function(t,n){t.setUTCDate(t.getUTCDate()+n)},function(t,n){return(n-t)/864e5},function(t){return t.getUTCDate()-1});function fe(t){return Qn(function(n){n.setUTCDate(n.getUTCDate()-(n.getUTCDay()+7-t)%7),n.setUTCHours(0,0,0,0)},function(t,n){t.setUTCDate(t.getUTCDate()+7*n)},function(t,n){return(n-t)/ee})}var le=fe(0),se=fe(1),he=(fe(2),fe(3),fe(4),fe(5),fe(6),Qn(function(t){t.setUTCDate(1),t.setUTCHours(0,0,0,0)},function(t,n){t.setUTCMonth(t.getUTCMonth()+n)},function(t,n){return n.getUTCMonth()-t.getUTCMonth()+12*(n.getUTCFullYear()-t.getUTCFullYear())},function(t){return t.getUTCMonth()}),Qn(function(t){t.setUTCMonth(0,1),t.setUTCHours(0,0,0,0)},function(t,n){t.setUTCFullYear(t.getUTCFullYear()+n)},function(t,n){return n.getUTCFullYear()-t.getUTCFullYear()},function(t){return t.getUTCFullYear()}));function de(t){if(0<=t.y&&t.y<100){var n=new Date(-1,t.m,t.d,t.H,t.M,t.S,t.L);return n.setFullYear(t.y),n}return new Date(t.y,t.m,t.d,t.H,t.M,t.S,t.L)}function pe(t){if(0<=t.y&&t.y<100){var n=new Date(Date.UTC(-1,t.m,t.d,t.H,t.M,t.S,t.L));return n.setUTCFullYear(t.y),n}return new Date(Date.UTC(t.y,t.m,t.d,t.H,t.M,t.S,t.L))}function ge(t){return{y:t,m:0,d:1,H:0,M:0,S:0,L:0}}he.every=function(t){return isFinite(t=Math.floor(t))&&t>0?Qn(function(n){n.setUTCFullYear(Math.floor(n.getUTCFullYear()/t)*t),n.setUTCMonth(0,1),n.setUTCHours(0,0,0,0)},function(n,e){n.setUTCFullYear(n.getUTCFullYear()+e*t)}):null};var be,ve,ye,me={"-":"",_:" ",0:"0"},we=/^\s*\d+/,_e=/^%/,Me=/[\\\^\$\*\+\?\|\[\]\(\)\.\{\}]/g;function xe(t,n,e){var r=t<0?"-":"",i=(r?-t:t)+"",a=i.length;return r+(a<e?new Array(e-a+1).join(n)+i:i)}function Te(t){return t.replace(Me,"\\$&")}function Ae(t){return new RegExp("^(?:"+t.map(Te).join("|")+")","i")}function Ce(t){for(var n={},e=-1,r=t.length;++e<r;)n[t[e].toLowerCase()]=e;return n}function Ne(t,n,e){var r=we.exec(n.slice(e,e+1));return r?(t.w=+r[0],e+r[0].length):-1}function Se(t,n,e){var r=we.exec(n.slice(e));return r?(t.U=+r[0],e+r[0].length):-1}function ke(t,n,e){var r=we.exec(n.slice(e));return r?(t.W=+r[0],e+r[0].length):-1}function Ee(t,n,e){var r=we.exec(n.slice(e,e+4));return r?(t.y=+r[0],e+r[0].length):-1}function Ue(t,n,e){var r=we.exec(n.slice(e,e+2));return r?(t.y=+r[0]+(+r[0]>68?1900:2e3),e+r[0].length):-1}function De(t,n,e){var r=/^(Z)|([+-]\d\d)(?:\:?(\d\d))?/.exec(n.slice(e,e+6));return r?(t.Z=r[1]?0:-(r[2]+(r[3]||"00")),e+r[0].length):-1}function He(t,n,e){var r=we.exec(n.slice(e,e+2));return r?(t.m=r[0]-1,e+r[0].length):-1}function Fe(t,n,e){var r=we.exec(n.slice(e,e+2));return r?(t.d=+r[0],e+r[0].length):-1}function Ye(t,n,e){var r=we.exec(n.slice(e,e+3));return r?(t.m=0,t.d=+r[0],e+r[0].length):-1}function Le(t,n,e){var r=we.exec(n.slice(e,e+2));return r?(t.H=+r[0],e+r[0].length):-1}function Pe(t,n,e){var r=we.exec(n.slice(e,e+2));return r?(t.M=+r[0],e+r[0].length):-1}function Oe(t,n,e){var r=we.exec(n.slice(e,e+2));return r?(t.S=+r[0],e+r[0].length):-1}function qe(t,n,e){var r=we.exec(n.slice(e,e+3));return r?(t.L=+r[0],e+r[0].length):-1}function je(t,n,e){var r=_e.exec(n.slice(e,e+1));return r?e+r[0].length:-1}function Xe(t,n){return xe(t.getDate(),n,2)}function ze(t,n){return xe(t.getHours(),n,2)}function Ie(t,n){return xe(t.getHours()%12||12,n,2)}function $e(t,n){return xe(1+re.count(ue(t),t),n,3)}function Be(t,n){return xe(t.getMilliseconds(),n,3)}function We(t,n){return xe(t.getMonth()+1,n,2)}function Re(t,n){return xe(t.getMinutes(),n,2)}function Ze(t,n){return xe(t.getSeconds(),n,2)}function Ve(t,n){return xe(ae.count(ue(t),t),n,2)}function Je(t){return t.getDay()}function Ge(t,n){return xe(oe.count(ue(t),t),n,2)}function Ke(t,n){return xe(t.getFullYear()%100,n,2)}function Qe(t,n){return xe(t.getFullYear()%1e4,n,4)}function tr(t){var n=t.getTimezoneOffset();return(n>0?"-":(n*=-1,"+"))+xe(n/60|0,"0",2)+xe(n%60,"0",2)}function nr(t,n){return xe(t.getUTCDate(),n,2)}function er(t,n){return xe(t.getUTCHours(),n,2)}function rr(t,n){return xe(t.getUTCHours()%12||12,n,2)}function ir(t,n){return xe(1+ce.count(he(t),t),n,3)}function ar(t,n){return xe(t.getUTCMilliseconds(),n,3)}function or(t,n){return xe(t.getUTCMonth()+1,n,2)}function ur(t,n){return xe(t.getUTCMinutes(),n,2)}function cr(t,n){return xe(t.getUTCSeconds(),n,2)}function fr(t,n){return xe(le.count(he(t),t),n,2)}function lr(t){return t.getUTCDay()}function sr(t,n){return xe(se.count(he(t),t),n,2)}function hr(t,n){return xe(t.getUTCFullYear()%100,n,2)}function dr(t,n){return xe(t.getUTCFullYear()%1e4,n,4)}function pr(){return"+0000"}function gr(){return"%"}!function(t){be=function(t){var n=t.dateTime,e=t.date,r=t.time,i=t.periods,a=t.days,o=t.shortDays,u=t.months,c=t.shortMonths,f=Ae(i),l=Ce(i),s=Ae(a),h=Ce(a),d=Ae(o),p=Ce(o),g=Ae(u),b=Ce(u),v=Ae(c),y=Ce(c),m={a:function(t){return o[t.getDay()]},A:function(t){return a[t.getDay()]},b:function(t){return c[t.getMonth()]},B:function(t){return u[t.getMonth()]},c:null,d:Xe,e:Xe,H:ze,I:Ie,j:$e,L:Be,m:We,M:Re,p:function(t){return i[+(t.getHours()>=12)]},S:Ze,U:Ve,w:Je,W:Ge,x:null,X:null,y:Ke,Y:Qe,Z:tr,"%":gr},w={a:function(t){return o[t.getUTCDay()]},A:function(t){return a[t.getUTCDay()]},b:function(t){return c[t.getUTCMonth()]},B:function(t){return u[t.getUTCMonth()]},c:null,d:nr,e:nr,H:er,I:rr,j:ir,L:ar,m:or,M:ur,p:function(t){return i[+(t.getUTCHours()>=12)]},S:cr,U:fr,w:lr,W:sr,x:null,X:null,y:hr,Y:dr,Z:pr,"%":gr},_={a:function(t,n,e){var r=d.exec(n.slice(e));return r?(t.w=p[r[0].toLowerCase()],e+r[0].length):-1},A:function(t,n,e){var r=s.exec(n.slice(e));return r?(t.w=h[r[0].toLowerCase()],e+r[0].length):-1},b:function(t,n,e){var r=v.exec(n.slice(e));return r?(t.m=y[r[0].toLowerCase()],e+r[0].length):-1},B:function(t,n,e){var r=g.exec(n.slice(e));return r?(t.m=b[r[0].toLowerCase()],e+r[0].length):-1},c:function(t,e,r){return T(t,n,e,r)},d:Fe,e:Fe,H:Le,I:Le,j:Ye,L:qe,m:He,M:Pe,p:function(t,n,e){var r=f.exec(n.slice(e));return r?(t.p=l[r[0].toLowerCase()],e+r[0].length):-1},S:Oe,U:Se,w:Ne,W:ke,x:function(t,n,r){return T(t,e,n,r)},X:function(t,n,e){return T(t,r,n,e)},y:Ue,Y:Ee,Z:De,"%":je};function M(t,n){return function(e){var r,i,a,o=[],u=-1,c=0,f=t.length;for(e instanceof Date||(e=new Date(+e));++u<f;)37===t.charCodeAt(u)&&(o.push(t.slice(c,u)),null!=(i=me[r=t.charAt(++u)])?r=t.charAt(++u):i="e"===r?" ":"0",(a=n[r])&&(r=a(e,i)),o.push(r),c=u+1);return o.push(t.slice(c,u)),o.join("")}}function x(t,n){return function(e){var r=ge(1900);if(T(r,t,e+="",0)!=e.length)return null;if("p"in r&&(r.H=r.H%12+12*r.p),"W"in r||"U"in r){"w"in r||(r.w="W"in r?1:0);var i="Z"in r?pe(ge(r.y)).getUTCDay():n(ge(r.y)).getDay();r.m=0,r.d="W"in r?(r.w+6)%7+7*r.W-(i+5)%7:r.w+7*r.U-(i+6)%7}return"Z"in r?(r.H+=r.Z/100|0,r.M+=r.Z%100,pe(r)):n(r)}}function T(t,n,e,r){for(var i,a,o=0,u=n.length,c=e.length;o<u;){if(r>=c)return-1;if(37===(i=n.charCodeAt(o++))){if(i=n.charAt(o++),!(a=_[i in me?n.charAt(o++):i])||(r=a(t,e,r))<0)return-1}else if(i!=e.charCodeAt(r++))return-1}return r}return m.x=M(e,m),m.X=M(r,m),m.c=M(n,m),w.x=M(e,w),w.X=M(r,w),w.c=M(n,w),{format:function(t){var n=M(t+="",m);return n.toString=function(){return t},n},parse:function(t){var n=x(t+="",de);return n.toString=function(){return t},n},utcFormat:function(t){var n=M(t+="",w);return n.toString=function(){return t},n},utcParse:function(t){var n=x(t,pe);return n.toString=function(){return t},n}}}(t),ve=be.utcFormat,ye=be.utcParse}({dateTime:"%x, %X",date:"%-m/%-d/%Y",time:"%-I:%M:%S %p",periods:["AM","PM"],days:["Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"],shortDays:["Sun","Mon","Tue","Wed","Thu","Fri","Sat"],months:["January","February","March","April","May","June","July","August","September","October","November","December"],shortMonths:["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"]});Date.prototype.toISOString||ve("%Y-%m-%dT%H:%M:%S.%LZ");+new Date("2000-01-01T00:00:00.000Z")||ye("%Y-%m-%dT%H:%M:%S.%LZ");var br=function(t){return t.match(/.{6}/g).map(function(t){return"#"+t})};br("1f77b4ff7f0e2ca02cd627289467bd8c564be377c27f7f7fbcbd2217becf"),br("393b795254a36b6ecf9c9ede6379398ca252b5cf6bcedb9c8c6d31bd9e39e7ba52e7cb94843c39ad494ad6616be7969c7b4173a55194ce6dbdde9ed6"),br("3182bd6baed69ecae1c6dbefe6550dfd8d3cfdae6bfdd0a231a35474c476a1d99bc7e9c0756bb19e9ac8bcbddcdadaeb636363969696bdbdbdd9d9d9"),br("1f77b4aec7e8ff7f0effbb782ca02c98df8ad62728ff98969467bdc5b0d58c564bc49c94e377c2f7b6d27f7f7fc7c7c7bcbd22dbdb8d17becf9edae5"),zn(yn(300,.5,0),yn(-240,.5,1));zn(yn(-100,.75,.35),yn(80,1.5,.8)),zn(yn(260,.75,.35),yn(80,1.5,.8)),yn();function vr(t){var n=t.length;return function(e){return t[Math.max(0,Math.min(n-1,Math.floor(e*n)))]}}vr(br("44015444025645045745055946075a46085c460a5d460b5e470d60470e6147106347116447136548146748166848176948186a481a6c481b6d481c6e481d6f481f70482071482173482374482475482576482677482878482979472a7a472c7a472d7b472e7c472f7d46307e46327e46337f463480453581453781453882443983443a83443b84433d84433e85423f854240864241864142874144874045884046883f47883f48893e49893e4a893e4c8a3d4d8a3d4e8a3c4f8a3c508b3b518b3b528b3a538b3a548c39558c39568c38588c38598c375a8c375b8d365c8d365d8d355e8d355f8d34608d34618d33628d33638d32648e32658e31668e31678e31688e30698e306a8e2f6b8e2f6c8e2e6d8e2e6e8e2e6f8e2d708e2d718e2c718e2c728e2c738e2b748e2b758e2a768e2a778e2a788e29798e297a8e297b8e287c8e287d8e277e8e277f8e27808e26818e26828e26828e25838e25848e25858e24868e24878e23888e23898e238a8d228b8d228c8d228d8d218e8d218f8d21908d21918c20928c20928c20938c1f948c1f958b1f968b1f978b1f988b1f998a1f9a8a1e9b8a1e9c891e9d891f9e891f9f881fa0881fa1881fa1871fa28720a38620a48621a58521a68522a78522a88423a98324aa8325ab8225ac8226ad8127ad8128ae8029af7f2ab07f2cb17e2db27d2eb37c2fb47c31b57b32b67a34b67935b77937b87838b9773aba763bbb753dbc743fbc7340bd7242be7144bf7046c06f48c16e4ac16d4cc26c4ec36b50c46a52c56954c56856c66758c7655ac8645cc8635ec96260ca6063cb5f65cb5e67cc5c69cd5b6ccd5a6ece5870cf5773d05675d05477d1537ad1517cd2507fd34e81d34d84d44b86d54989d5488bd6468ed64590d74393d74195d84098d83e9bd93c9dd93ba0da39a2da37a5db36a8db34aadc32addc30b0dd2fb2dd2db5de2bb8de29bade28bddf26c0df25c2df23c5e021c8e020cae11fcde11dd0e11cd2e21bd5e21ad8e219dae319dde318dfe318e2e418e5e419e7e419eae51aece51befe51cf1e51df4e61ef6e620f8e621fbe723fde725"));vr(br("00000401000501010601010802010902020b02020d03030f03031204041405041606051806051a07061c08071e0907200a08220b09240c09260d0a290e0b2b100b2d110c2f120d31130d34140e36150e38160f3b180f3d19103f1a10421c10441d11471e114920114b21114e22115024125325125527125829115a2a115c2c115f2d11612f116331116533106734106936106b38106c390f6e3b0f703d0f713f0f72400f74420f75440f764510774710784910784a10794c117a4e117b4f127b51127c52137c54137d56147d57157e59157e5a167e5c167f5d177f5f187f601880621980641a80651a80671b80681c816a1c816b1d816d1d816e1e81701f81721f817320817521817621817822817922827b23827c23827e24828025828125818326818426818627818827818928818b29818c29818e2a81902a81912b81932b80942c80962c80982d80992d809b2e7f9c2e7f9e2f7fa02f7fa1307ea3307ea5317ea6317da8327daa337dab337cad347cae347bb0357bb2357bb3367ab5367ab73779b83779ba3878bc3978bd3977bf3a77c03a76c23b75c43c75c53c74c73d73c83e73ca3e72cc3f71cd4071cf4070d0416fd2426fd3436ed5446dd6456cd8456cd9466bdb476adc4869de4968df4a68e04c67e24d66e34e65e44f64e55064e75263e85362e95462ea5661eb5760ec5860ed5a5fee5b5eef5d5ef05f5ef1605df2625df2645cf3655cf4675cf4695cf56b5cf66c5cf66e5cf7705cf7725cf8745cf8765cf9785df9795df97b5dfa7d5efa7f5efa815ffb835ffb8560fb8761fc8961fc8a62fc8c63fc8e64fc9065fd9266fd9467fd9668fd9869fd9a6afd9b6bfe9d6cfe9f6dfea16efea36ffea571fea772fea973feaa74feac76feae77feb078feb27afeb47bfeb67cfeb77efeb97ffebb81febd82febf84fec185fec287fec488fec68afec88cfeca8dfecc8ffecd90fecf92fed194fed395fed597fed799fed89afdda9cfddc9efddea0fde0a1fde2a3fde3a5fde5a7fde7a9fde9aafdebacfcecaefceeb0fcf0b2fcf2b4fcf4b6fcf6b8fcf7b9fcf9bbfcfbbdfcfdbf")),vr(br("00000401000501010601010802010a02020c02020e03021004031204031405041706041907051b08051d09061f0a07220b07240c08260d08290e092b10092d110a30120a32140b34150b37160b39180c3c190c3e1b0c411c0c431e0c451f0c48210c4a230c4c240c4f260c51280b53290b552b0b572d0b592f0a5b310a5c320a5e340a5f3609613809623909633b09643d09653e0966400a67420a68440a68450a69470b6a490b6a4a0c6b4c0c6b4d0d6c4f0d6c510e6c520e6d540f6d550f6d57106e59106e5a116e5c126e5d126e5f136e61136e62146e64156e65156e67166e69166e6a176e6c186e6d186e6f196e71196e721a6e741a6e751b6e771c6d781c6d7a1d6d7c1d6d7d1e6d7f1e6c801f6c82206c84206b85216b87216b88226a8a226a8c23698d23698f24699025689225689326679526679727669827669a28659b29649d29649f2a63a02a63a22b62a32c61a52c60a62d60a82e5fa92e5eab2f5ead305dae305cb0315bb1325ab3325ab43359b63458b73557b93556ba3655bc3754bd3853bf3952c03a51c13a50c33b4fc43c4ec63d4dc73e4cc83f4bca404acb4149cc4248ce4347cf4446d04545d24644d34743d44842d54a41d74b3fd84c3ed94d3dda4e3cdb503bdd513ade5238df5337e05536e15635e25734e35933e45a31e55c30e65d2fe75e2ee8602de9612bea632aeb6429eb6628ec6726ed6925ee6a24ef6c23ef6e21f06f20f1711ff1731df2741cf3761bf37819f47918f57b17f57d15f67e14f68013f78212f78410f8850ff8870ef8890cf98b0bf98c0af98e09fa9008fa9207fa9407fb9606fb9706fb9906fb9b06fb9d07fc9f07fca108fca309fca50afca60cfca80dfcaa0ffcac11fcae12fcb014fcb216fcb418fbb61afbb81dfbba1ffbbc21fbbe23fac026fac228fac42afac62df9c72ff9c932f9cb35f8cd37f8cf3af7d13df7d340f6d543f6d746f5d949f5db4cf4dd4ff4df53f4e156f3e35af3e55df2e661f2e865f2ea69f1ec6df1ed71f1ef75f1f179f2f27df2f482f3f586f3f68af4f88ef5f992f6fa96f8fb9af9fc9dfafda1fcffa4")),vr(br("0d088710078813078916078a19068c1b068d1d068e20068f2206902406912605912805922a05932c05942e05952f059631059733059735049837049938049a3a049a3c049b3e049c3f049c41049d43039e44039e46039f48039f4903a04b03a14c02a14e02a25002a25102a35302a35502a45601a45801a45901a55b01a55c01a65e01a66001a66100a76300a76400a76600a76700a86900a86a00a86c00a86e00a86f00a87100a87201a87401a87501a87701a87801a87a02a87b02a87d03a87e03a88004a88104a78305a78405a78606a68707a68808a68a09a58b0aa58d0ba58e0ca48f0da4910ea3920fa39410a29511a19613a19814a099159f9a169f9c179e9d189d9e199da01a9ca11b9ba21d9aa31e9aa51f99a62098a72197a82296aa2395ab2494ac2694ad2793ae2892b02991b12a90b22b8fb32c8eb42e8db52f8cb6308bb7318ab83289ba3388bb3488bc3587bd3786be3885bf3984c03a83c13b82c23c81c33d80c43e7fc5407ec6417dc7427cc8437bc9447aca457acb4679cc4778cc4977cd4a76ce4b75cf4c74d04d73d14e72d24f71d35171d45270d5536fd5546ed6556dd7566cd8576bd9586ada5a6ada5b69db5c68dc5d67dd5e66de5f65de6164df6263e06363e16462e26561e26660e3685fe4695ee56a5de56b5de66c5ce76e5be76f5ae87059e97158e97257ea7457eb7556eb7655ec7754ed7953ed7a52ee7b51ef7c51ef7e50f07f4ff0804ef1814df1834cf2844bf3854bf3874af48849f48948f58b47f58c46f68d45f68f44f79044f79143f79342f89441f89540f9973ff9983ef99a3efa9b3dfa9c3cfa9e3bfb9f3afba139fba238fca338fca537fca636fca835fca934fdab33fdac33fdae32fdaf31fdb130fdb22ffdb42ffdb52efeb72dfeb82cfeba2cfebb2bfebd2afebe2afec029fdc229fdc328fdc527fdc627fdc827fdca26fdcb26fccd25fcce25fcd025fcd225fbd324fbd524fbd724fad824fada24f9dc24f9dd25f8df25f8e125f7e225f7e425f6e626f6e826f5e926f5eb27f4ed27f3ee27f3f027f2f227f1f426f1f525f0f724f0f921"));function yr(t){return((t*=2)<=1?t*t*t:(t-=2)*t*t+2)/2}var mr="undefined"!=typeof window?window:"undefined"!=typeof global?global:"undefined"!=typeof self?self:{};var wr,_r=(function(t){!function(e,r){if(t.exports){var i=n;t.exports=r(i)}else e.d3.tip=r(e.d3)}(mr,function(t){return function(){var n=function(){return"n"},e=function(){return[0,0]},r=function(){return" "},i=s(),a=null,o=null,u=null;function c(t){var n;a="svg"===(n=(n=t).node()).tagName.toLowerCase()?n:n.ownerSVGElement,o=a.createSVGPoint(),document.body.appendChild(i)}c.show=function(){var t=Array.prototype.slice.call(arguments);t[t.length-1]instanceof SVGElement&&(u=t.pop());var i,a=r.apply(this,t),o=e.apply(this,t),s=n.apply(this,t),d=h(),p=l.length,g=document.documentElement.scrollTop||document.body.scrollTop,b=document.documentElement.scrollLeft||document.body.scrollLeft;for(d.html(a).style("opacity",1).style("pointer-events","all");p--;)d.classed(l[p],!1);return i=f.get(s).apply(this),d.classed(s,!0).style("top",i.top+o[0]+g+"px").style("left",i.left+o[1]+b+"px"),c},c.hide=function(){return h().style("opacity",0).style("pointer-events","none"),c},c.attr=function(n,e){if(arguments.length<2&&"string"==typeof n)return h().attr(n);var r=Array.prototype.slice.call(arguments);return t.selection.prototype.attr.apply(h(),r),c},c.style=function(n,e){if(arguments.length<2&&"string"==typeof n)return h().style(n);var r=Array.prototype.slice.call(arguments);return t.selection.prototype.style.apply(h(),r),c},c.direction=function(t){return arguments.length?(n=null==t?t:p(t),c):n},c.offset=function(t){return arguments.length?(e=null==t?t:p(t),c):e},c.html=function(t){return arguments.length?(r=null==t?t:p(t),c):r},c.destroy=function(){return i&&(h().remove(),i=null),c};var f=t.map({n:function(){var t=d();return{top:t.n.y-i.offsetHeight,left:t.n.x-i.offsetWidth/2}},s:function(){var t=d();return{top:t.s.y,left:t.s.x-i.offsetWidth/2}},e:function(){var t=d();return{top:t.e.y-i.offsetHeight/2,left:t.e.x}},w:function(){var t=d();return{top:t.w.y-i.offsetHeight/2,left:t.w.x-i.offsetWidth}},nw:function(){var t=d();return{top:t.nw.y-i.offsetHeight,left:t.nw.x-i.offsetWidth}},ne:function(){var t=d();return{top:t.ne.y-i.offsetHeight,left:t.ne.x}},sw:function(){var t=d();return{top:t.sw.y,left:t.sw.x-i.offsetWidth}},se:function(){var t=d();return{top:t.se.y,left:t.e.x}}}),l=f.keys();function s(){var n=t.select(document.createElement("div"));return n.style("position","absolute").style("top",0).style("opacity",0).style("pointer-events","none").style("box-sizing","border-box"),n.node()}function h(){return null===i&&(i=s(),document.body.appendChild(i)),t.select(i)}function d(){for(var n=u||t.event.target;void 0===n.getScreenCTM&&"undefined"===n.parentNode;)n=n.parentNode;var e={},r=n.getScreenCTM(),i=n.getBBox(),a=i.width,c=i.height,f=i.x,l=i.y;return o.x=f,o.y=l,e.nw=o.matrixTransform(r),o.x+=a,e.ne=o.matrixTransform(r),o.y+=c,e.se=o.matrixTransform(r),o.x-=a,e.sw=o.matrixTransform(r),o.y-=c/2,e.w=o.matrixTransform(r),o.x+=a,e.e=o.matrixTransform(r),o.x-=a/2,o.y-=c/2,e.n=o.matrixTransform(r),o.y+=c,e.s=o.matrixTransform(r),e}function p(t){return"function"==typeof t?t:function(){return t}}return c}})}(wr={exports:{}},wr.exports),wr.exports),Mr={value:function(){}};function xr(){for(var t,n=0,e=arguments.length,r={};n<e;++n){if(!(t=arguments[n]+"")||t in r)throw new Error("illegal type: "+t);r[t]=[]}return new Tr(r)}function Tr(t){this._=t}function Ar(t,n){for(var e,r=0,i=t.length;r<i;++r)if((e=t[r]).name===n)return e.value}function Cr(t,n,e){for(var r=0,i=t.length;r<i;++r)if(t[r].name===n){t[r]=Mr,t=t.slice(0,r).concat(t.slice(r+1));break}return null!=e&&t.push({name:n,value:e}),t}Tr.prototype=xr.prototype={constructor:Tr,on:function(t,n){var e,r,i=this._,a=(r=i,(t+"").trim().split(/^|\s+/).map(function(t){var n="",e=t.indexOf(".");if(e>=0&&(n=t.slice(e+1),t=t.slice(0,e)),t&&!r.hasOwnProperty(t))throw new Error("unknown type: "+t);return{type:t,name:n}})),o=-1,u=a.length;if(!(arguments.length<2)){if(null!=n&&"function"!=typeof n)throw new Error("invalid callback: "+n);for(;++o<u;)if(e=(t=a[o]).type)i[e]=Cr(i[e],t.name,n);else if(null==n)for(e in i)i[e]=Cr(i[e],t.name,null);return this}for(;++o<u;)if((e=(t=a[o]).type)&&(e=Ar(i[e],t.name)))return e},copy:function(){var t={},n=this._;for(var e in n)t[e]=n[e].slice();return new Tr(t)},call:function(t,n){if((e=arguments.length-2)>0)for(var e,r,i=new Array(e),a=0;a<e;++a)i[a]=arguments[a+2];if(!this._.hasOwnProperty(t))throw new Error("unknown type: "+t);for(a=0,e=(r=this._[t]).length;a<e;++a)r[a].value.apply(n,i)},apply:function(t,n,e){if(!this._.hasOwnProperty(t))throw new Error("unknown type: "+t);for(var r=this._[t],i=0,a=r.length;i<a;++i)r[i].value.apply(n,e)}};var Nr,Sr,kr=0,Er=0,Ur=0,Dr=1e3,Hr=0,Fr=0,Yr=0,Lr="object"==typeof performance&&performance.now?performance:Date,Pr="object"==typeof window&&window.requestAnimationFrame?window.requestAnimationFrame.bind(window):function(t){setTimeout(t,17)};function Or(){return Fr||(Pr(qr),Fr=Lr.now()+Yr)}function qr(){Fr=0}function jr(){this._call=this._time=this._next=null}function Xr(t,n,e){var r=new jr;return r.restart(t,n,e),r}function zr(){Fr=(Hr=Lr.now())+Yr,kr=Er=0;try{!function(){Or(),++kr;for(var t,n=Nr;n;)(t=Fr-n._time)>=0&&n._call.call(null,t),n=n._next;--kr}()}finally{kr=0,function(){var t,n,e=Nr,r=1/0;for(;e;)e._call?(r>e._time&&(r=e._time),t=e,e=e._next):(n=e._next,e._next=null,e=t?t._next=n:Nr=n);Sr=t,$r(r)}(),Fr=0}}function Ir(){var t=Lr.now(),n=t-Hr;n>Dr&&(Yr-=n,Hr=t)}function $r(t){if(!kr){Er&&(Er=clearTimeout(Er));var n=t-Fr;n>24?(t<1/0&&(Er=setTimeout(zr,n)),Ur&&(Ur=clearInterval(Ur))):(Ur||(Hr=Fr,Ur=setInterval(Ir,Dr)),kr=1,Pr(zr))}}jr.prototype=Xr.prototype={constructor:jr,restart:function(t,n,e){if("function"!=typeof t)throw new TypeError("callback is not a function");e=(null==e?Or():+e)+(null==n?0:+n),this._next||Sr===this||(Sr?Sr._next=this:Nr=this,Sr=this),this._call=t,this._time=e,$r()},stop:function(){this._call&&(this._call=null,this._time=1/0,$r())}};var Br=function(t,n,e){var r=new jr;return n=null==n?0:+n,r.restart(function(e){r.stop(),t(e+n)},n,e),r},Wr=xr("start","end","interrupt"),Rr=[],Zr=0,Vr=1,Jr=2,Gr=3,Kr=4,Qr=5,ti=6,ni=function(t,n,e,r,i,a){var o=t.__transition;if(o){if(e in o)return}else t.__transition={};!function(t,n,e){var r,i=t.__transition;function a(c){var f,l,s,h;if(e.state!==Vr)return u();for(f in i)if((h=i[f]).name===e.name){if(h.state===Gr)return Br(a);h.state===Kr?(h.state=ti,h.timer.stop(),h.on.call("interrupt",t,t.__data__,h.index,h.group),delete i[f]):+f<n&&(h.state=ti,h.timer.stop(),delete i[f])}if(Br(function(){e.state===Gr&&(e.state=Kr,e.timer.restart(o,e.delay,e.time),o(c))}),e.state=Jr,e.on.call("start",t,t.__data__,e.index,e.group),e.state===Jr){for(e.state=Gr,r=new Array(s=e.tween.length),f=0,l=-1;f<s;++f)(h=e.tween[f].value.call(t,t.__data__,e.index,e.group))&&(r[++l]=h);r.length=l+1}}function o(n){for(var i=n<e.duration?e.ease.call(null,n/e.duration):(e.timer.restart(u),e.state=Qr,1),a=-1,o=r.length;++a<o;)r[a].call(null,i);e.state===Qr&&(e.on.call("end",t,t.__data__,e.index,e.group),u())}function u(){for(var r in e.state=ti,e.timer.stop(),delete i[n],i)return;delete t.__transition}i[n]=e,e.timer=Xr(function(t){e.state=Vr,e.timer.restart(a,e.delay,e.time),e.delay<=t&&a(t-e.delay)},0,e.time)}(t,e,{name:n,index:r,group:i,on:Wr,tween:Rr,time:a.time,delay:a.delay,duration:a.duration,ease:a.ease,timer:null,state:Zr})};function ei(t,n){var e=t.__transition;if(!e||!(e=e[n])||e.state>Zr)throw new Error("too late");return e}function ri(t,n){var e=t.__transition;if(!e||!(e=e[n])||e.state>Jr)throw new Error("too late");return e}function ii(t,n){var e=t.__transition;if(!e||!(e=e[n]))throw new Error("too late");return e}function ai(t,n,e){var r=t._id;return t.each(function(){var t=ri(this,r);(t.value||(t.value={}))[n]=e.apply(this,arguments)}),function(t){return ii(t,r).value[n]}}var oi=function(t,n){var e;return("number"==typeof n?An:n instanceof Ot?Tn:(e=Ot(n))?(n=e,Tn):Dn)(t,n)};var ui=X.prototype.constructor;var ci=0;function fi(t,n,e,r){this._groups=t,this._parents=n,this._name=e,this._id=r}function li(){return++ci}var si=X.prototype;fi.prototype=function(t){return X().transition(t)}.prototype={constructor:fi,select:function(t){var n=this._name,e=this._id;"function"!=typeof t&&(t=b(t));for(var r=this._groups,i=r.length,a=new Array(i),o=0;o<i;++o)for(var u,c,f=r[o],l=f.length,s=a[o]=new Array(l),h=0;h<l;++h)(u=f[h])&&(c=t.call(u,u.__data__,h,f))&&("__data__"in u&&(c.__data__=u.__data__),s[h]=c,ni(s[h],n,e,h,s,ii(u,e)));return new fi(a,this._parents,n,e)},selectAll:function(t){var n=this._name,e=this._id;"function"!=typeof t&&(t=y(t));for(var r=this._groups,i=r.length,a=[],o=[],u=0;u<i;++u)for(var c,f=r[u],l=f.length,s=0;s<l;++s)if(c=f[s]){for(var h,d=t.call(c,c.__data__,s,f),p=ii(c,e),g=0,b=d.length;g<b;++g)(h=d[g])&&ni(h,n,e,g,d,p);a.push(d),o.push(c)}return new fi(a,o,n,e)},filter:function(t){"function"!=typeof t&&(t=f(t));for(var n=this._groups,e=n.length,r=new Array(e),i=0;i<e;++i)for(var a,o=n[i],u=o.length,c=r[i]=[],l=0;l<u;++l)(a=o[l])&&t.call(a,a.__data__,l,o)&&c.push(a);return new fi(r,this._parents,this._name,this._id)},merge:function(t){if(t._id!==this._id)throw new Error;for(var n=this._groups,e=t._groups,r=n.length,i=e.length,a=Math.min(r,i),o=new Array(r),u=0;u<a;++u)for(var c,f=n[u],l=e[u],s=f.length,h=o[u]=new Array(s),d=0;d<s;++d)(c=f[d]||l[d])&&(h[d]=c);for(;u<r;++u)o[u]=n[u];return new fi(o,this._parents,this._name,this._id)},selection:function(){return new ui(this._groups,this._parents)},transition:function(){for(var t=this._name,n=this._id,e=li(),r=this._groups,i=r.length,a=0;a<i;++a)for(var o,u=r[a],c=u.length,f=0;f<c;++f)if(o=u[f]){var l=ii(o,n);ni(o,t,e,f,u,{time:l.time+l.delay+l.duration,delay:0,duration:l.duration,ease:l.ease})}return new fi(r,this._parents,t,e)},call:si.call,nodes:si.nodes,node:si.node,size:si.size,empty:si.empty,each:si.each,on:function(t,n){var e=this._id;return arguments.length<2?ii(this.node(),e).on.on(t):this.each(function(t,n,e){var r,i,a=function(t){return(t+"").trim().split(/^|\s+/).every(function(t){var n=t.indexOf(".");return n>=0&&(t=t.slice(0,n)),!t||"start"===t})}(n)?ei:ri;return function(){var o=a(this,t),u=o.on;u!==r&&(i=(r=u).copy()).on(n,e),o.on=i}}(e,t,n))},attr:function(t,n){var e=i(t),r="transform"===e?jn:oi;return this.attrTween(t,"function"==typeof n?(e.local?function(t,n,e){var r,i,a;return function(){var o,u=e(this);if(null!=u)return(o=this.getAttributeNS(t.space,t.local))===u?null:o===r&&u===i?a:a=n(r=o,i=u);this.removeAttributeNS(t.space,t.local)}}:function(t,n,e){var r,i,a;return function(){var o,u=e(this);if(null!=u)return(o=this.getAttribute(t))===u?null:o===r&&u===i?a:a=n(r=o,i=u);this.removeAttribute(t)}})(e,r,ai(this,"attr."+t,n)):null==n?(e.local?function(t){return function(){this.removeAttributeNS(t.space,t.local)}}:function(t){return function(){this.removeAttribute(t)}})(e):(e.local?function(t,n,e){var r,i;return function(){var a=this.getAttributeNS(t.space,t.local);return a===e?null:a===r?i:i=n(r=a,e)}}:function(t,n,e){var r,i;return function(){var a=this.getAttribute(t);return a===e?null:a===r?i:i=n(r=a,e)}})(e,r,n+""))},attrTween:function(t,n){var e="attr."+t;if(arguments.length<2)return(e=this.tween(e))&&e._value;if(null==n)return this.tween(e,null);if("function"!=typeof n)throw new Error;var r=i(t);return this.tween(e,(r.local?function(t,n){function e(){var e=this,r=n.apply(e,arguments);return r&&function(n){e.setAttributeNS(t.space,t.local,r(n))}}return e._value=n,e}:function(t,n){function e(){var e=this,r=n.apply(e,arguments);return r&&function(n){e.setAttribute(t,r(n))}}return e._value=n,e})(r,n))},style:function(t,n,e){var r="transform"==(t+="")?qn:oi;return null==n?this.styleTween(t,function(t,n){var e,r,i;return function(){var a=C(this,t),o=(this.style.removeProperty(t),C(this,t));return a===o?null:a===e&&o===r?i:i=n(e=a,r=o)}}(t,r)).on("end.style."+t,function(t){return function(){this.style.removeProperty(t)}}(t)):this.styleTween(t,"function"==typeof n?function(t,n,e){var r,i,a;return function(){var o=C(this,t),u=e(this);return null==u&&(this.style.removeProperty(t),u=C(this,t)),o===u?null:o===r&&u===i?a:a=n(r=o,i=u)}}(t,r,ai(this,"style."+t,n)):function(t,n,e){var r,i;return function(){var a=C(this,t);return a===e?null:a===r?i:i=n(r=a,e)}}(t,r,n+""),e)},styleTween:function(t,n,e){var r="style."+(t+="");if(arguments.length<2)return(r=this.tween(r))&&r._value;if(null==n)return this.tween(r,null);if("function"!=typeof n)throw new Error;return this.tween(r,function(t,n,e){function r(){var r=this,i=n.apply(r,arguments);return i&&function(n){r.style.setProperty(t,i(n),e)}}return r._value=n,r}(t,n,null==e?"":e))},text:function(t){return this.tween("text","function"==typeof t?function(t){return function(){var n=t(this);this.textContent=null==n?"":n}}(ai(this,"text",t)):function(t){return function(){this.textContent=t}}(null==t?"":t+""))},remove:function(){return this.on("end.remove",(t=this._id,function(){var n=this.parentNode;for(var e in this.__transition)if(+e!==t)return;n&&n.removeChild(this)}));var t},tween:function(t,n){var e=this._id;if(t+="",arguments.length<2){for(var r,i=ii(this.node(),e).tween,a=0,o=i.length;a<o;++a)if((r=i[a]).name===t)return r.value;return null}return this.each((null==n?function(t,n){var e,r;return function(){var i=ri(this,t),a=i.tween;if(a!==e)for(var o=0,u=(r=e=a).length;o<u;++o)if(r[o].name===n){(r=r.slice()).splice(o,1);break}i.tween=r}}:function(t,n,e){var r,i;if("function"!=typeof e)throw new Error;return function(){var a=ri(this,t),o=a.tween;if(o!==r){i=(r=o).slice();for(var u={name:n,value:e},c=0,f=i.length;c<f;++c)if(i[c].name===n){i[c]=u;break}c===f&&i.push(u)}a.tween=i}})(e,t,n))},delay:function(t){var n=this._id;return arguments.length?this.each(("function"==typeof t?function(t,n){return function(){ei(this,t).delay=+n.apply(this,arguments)}}:function(t,n){return n=+n,function(){ei(this,t).delay=n}})(n,t)):ii(this.node(),n).delay},duration:function(t){var n=this._id;return arguments.length?this.each(("function"==typeof t?function(t,n){return function(){ri(this,t).duration=+n.apply(this,arguments)}}:function(t,n){return n=+n,function(){ri(this,t).duration=n}})(n,t)):ii(this.node(),n).duration},ease:function(t){var n=this._id;return arguments.length?this.each(function(t,n){if("function"!=typeof n)throw new Error;return function(){ri(this,t).ease=n}}(n,t)):ii(this.node(),n).ease}};var hi={time:null,delay:0,duration:250,ease:yr};function di(t,n){for(var e;!(e=t.__transition)||!(e=e[n]);)if(!(t=t.parentNode))return hi.time=Or(),hi;return e}X.prototype.interrupt=function(t){return this.each(function(){!function(t,n){var e,r,i,a=t.__transition,o=!0;if(a){for(i in n=null==n?null:n+"",a)(e=a[i]).name===n?(r=e.state>Jr&&e.state<Qr,e.state=ti,e.timer.stop(),r&&e.on.call("interrupt",t,t.__data__,e.index,e.group),delete a[i]):o=!1;o&&delete t.__transition}}(this,t)})},X.prototype.transition=function(t){var n,e;t instanceof fi?(n=t._id,t=t._name):(n=li(),(e=hi).time=Or(),t=null==t?null:t+"");for(var r=this._groups,i=r.length,a=0;a<i;++a)for(var o,u=r[a],c=u.length,f=0;f<c;++f)(o=u[f])&&ni(o,t,n,f,u,e||di(o,n));return new fi(r,this._parents,t,n)};t.flamegraph=function(){var t,n=960,e=null,r=18,i=null,a=!0,o="",u=750,c=yr,f=!1,l=!1,s=null,h=0,d=null,p=!1,g=!1,b=!1,v=0,y=0,m=0,w=function(){d&&E()},_=w,M=function(t){d&&(t?d.innerHTML=t:v?E():d.innerHTML="")},x=M,T=function(t){return C(t)+" ("+K(".3f")(100*(t.x1-t.x0),3)+"%, "+N(t)+" bytes)"},A=_r().direction("s").offset([8,0]).attr("class","d3-flame-graph-tip").html(function(t){return T(t)});function C(t){return t.data.n||t.data.name}function N(t){return t.v||t.value}function S(t){return t.c||t.children}function k(t){return t.data.d||t.data.delta}function E(){d.innerHTML=`${v} of ${y} samples (${K(".3f")(v/y*100,3)}%)`}var U=function(t){return t.highlight?"#E600E6":function(t,n,e){var r,i,a;if(g)r=220,i=220,a=220,e||(e=0),e>0?(a=Math.round(210*(m-e)/m),i=a):e<0&&(r=Math.round(210*(m+e)/m),i=r);else{var o=b?"cold":"warm";b||void 0===n||""===n||(o="red",void 0!==t&&t&&t.match(/::/)&&(o="yellow"),"kernel"===n?o="orange":"jit"===n?o="green":"inlined"===n&&(o="aqua"));var u=0;if(t){var c=t.split("`");c.length>1&&(t=c[c.length-1]),t=t.split("(")[0],u=function(t){var n=0,e=0,r=1;if(t){for(var i=0;i<t.length&&!(i>6);i++)n+=r*(t.charCodeAt(i)%10),e+=9*r,r*=.7;e>0&&(n/=e)}return n}(t)}"red"===o?(r=200+Math.round(55*u),i=50+Math.round(80*u),a=i):"orange"===o?(r=190+Math.round(65*u),i=90+Math.round(65*u),a=0):"yellow"===o?(r=175+Math.round(55*u),i=r,a=50+Math.round(20*u)):"green"===o?(r=50+Math.round(60*u),i=200+Math.round(55*u),a=r):"aqua"===o?(r=50+Math.round(60*u),i=165+Math.round(55*u),a=i):"cold"===o?(r=0+Math.round(55*(1-u)),i=0+Math.round(230*(1-u)),a=200+Math.round(55*u)):(r=200+Math.round(55*u),i=0+Math.round(230*(1-u)),a=0+Math.round(55*(1-u)))}return"rgb("+r+","+i+","+a+")"}(C(t),function(t){return t.data.l||t.data.libtype}(t),k(t))},D=U;function H(t){t.data.hide=!0,S(t)&&S(t).forEach(H)}function F(t){t.data.fade=!1,t.data.hide=!1,S(t)&&S(t).forEach(F)}function Y(t){(function(t){var n=[];if(t.parent){var e=S(t.parent).indexOf(t);(n=S(t.parent).slice(0)).splice(e,1)}return n})(t).forEach(function(t){H(t)}),t.parent&&Y(t.parent)}function L(t){A.hide(t),Y(t),F(t),function t(n){n.parent&&(n.parent.data.fade=!0,t(n.parent))}(t),q(),"function"==typeof s&&s(t)}function P(t,n){return"function"==typeof f?f(t,n):f?et(C(t),C(n)):void 0}var O=mt();function q(){i.each(function(t){var i=Jn().range([0,n]),o=Jn().range([0,r]);f&&t.sort(P),t.sum(function(t){if(t.fade||t.hide)return 0;var n=N(t);if(!p&&S(t))for(var e=S(t),r=0;r<e.length;r++)n-=N(e[r]);return n}),O(t);var s=n/(t.x1-t.x0);function d(t){return(t.x1-t.x0)*s}var g=function(t){var e=t.descendants();if(h>0){var r=n/(t.x1-t.x0);e=e.filter(function(t){return(t.x1-t.x0)*r>h})}return e}(t),b=I(this).select("svg").selectAll("g").data(g,function(t){return t.id});if(!e){var v=Math.max.apply(null,g.map(function(t){return t.depth}));e=(v+2)*r,I(this).select("svg").attr("height",e)}b.transition().duration(u).ease(c).attr("transform",function(t){return"translate("+i(t.x0)+","+(l?o(t.depth):e-o(t.depth)-r)+")"}),b.select("rect").transition().duration(u).ease(c).attr("width",d);var y=b.enter().append("svg:g").attr("transform",function(t){return"translate("+i(t.x0)+","+(l?o(t.depth):e-o(t.depth)-r)+")"});y.append("svg:rect").transition().delay(u/2).attr("width",d),a||y.append("svg:title"),y.append("foreignObject").append("xhtml:div"),(b=I(this).select("svg").selectAll("g").data(g,function(t){return t.id})).attr("width",d).attr("height",function(t){return r}).attr("name",function(t){return C(t)}).attr("class",function(t){return t.data.fade?"frame fade":"frame"}),b.select("rect").attr("height",function(t){return r}).attr("fill",function(t){return U(t)}),a||b.select("title").text(T),b.select("foreignObject").attr("width",d).attr("height",function(t){return r}).select("div").attr("class","d3-flame-graph-label").style("display",function(t){return d(t)<1?"none":"block"}).transition().delay(u).text(C),b.on("click",L),b.exit().remove(),b.on("mouseover",function(t){a&&A.show(t,this),M(T(t))}).on("mouseout",function(t){a&&A.hide(t),M(null)})})}function j(){return Math.floor(65536*(1+Math.random())).toString(16).substring(1)}function X(t){t.id=j()+"-"+j()+"--"+j()+"-"+j();for(var n=S(t)||[],e=0;e<n.length;e++)X(n[e])}function z(a){var u=ht(a.datum(),function(t){return S(t)});if(X(u),y=N(u),g&&function t(n){var e=Math.abs(k(n));m=e>m?e:m;for(var r=S(n)||[],i=0;i<r.length;i++)t(r[i])}(u),i=a.datum(u),!arguments.length)return z;i.each(function(i){t||(t=I(this).append("svg:svg").attr("width",n).attr("height",e||(u.height+2)*r).attr("class","partition d3-flame-graph").call(A)).append("svg:text").attr("class","title").attr("text-anchor","middle").attr("y","25").attr("x",n/2).attr("fill","#808080").text(o)}),q()}return z.height=function(t){return arguments.length?(e=t,z):e},z.width=function(t){return arguments.length?(n=t,z):n},z.cellHeight=function(t){return arguments.length?(r=t,z):r},z.tooltip=function(t){return arguments.length?("function"==typeof t&&(A=t),a=!!t,z):a},z.title=function(t){return arguments.length?(o=t,z):o},z.transitionDuration=function(t){return arguments.length?(u=t,z):u},z.transitionEase=function(t){return arguments.length?(c=t,z):c},z.sort=function(t){return arguments.length?(f=t,z):f},z.inverted=function(t){return arguments.length?(l=t,z):l},z.differential=function(t){return arguments.length?(g=t,z):g},z.elided=function(t){return arguments.length?(b=t,z):b},z.setLabelHandler=function(t){return arguments.length?(T=t,z):T},z.label=z.setLabelHandler,z.search=function(t){i.each(function(n){!function(t,n){var e=new RegExp(n),r=[],i=0;!function t(n,a){var o=C(n),u=!1;void 0!==o&&o&&o.match(e)?(n.highlight=!0,u=!0,a||(i+=N(n)),r.push(n)):n.highlight=!1,S(n)&&S(n).forEach(function(n){t(n,a||u)})}(t,!1),v=i,w(r,i,y)}(n,t),q()})},z.clear=function(){v=0,M(null),i.each(function(t){!function t(n){n.highlight=!1,S(n)&&S(n).forEach(function(n){t(n)})}(t),q()})},z.zoomTo=function(t){L(t)},z.resetZoom=function(){i.each(function(t){L(t)})},z.onClick=function(t){return arguments.length?(s=t,z):s},z.merge=function(t){var n;i.each(function(e){!function t(n,e){e.forEach(function(e){var r=n.find(function(t){return t.name===e.name});r?(r.original?r.original+=e.value:r.value+=e.value,e.children&&(r.children||(r.children=[]),t(r.children,e.children))):n.push(e)})}([e.data],[t]),X(n=ht(e.data,function(t){return S(t)}))}),i=i.datum(n),q()},z.setColorMapper=function(t){return arguments.length?(U=t,z):(U=D,z)},z.color=z.setColorMapper,z.minFrameSize=function(t){return arguments.length?(h=t,z):h},z.setDetailsElement=function(t){return arguments.length?(d=t,z):d},z.details=z.setDetailsElement,z.selfValue=function(t){return arguments.length?(p=t,z):p},z.setSearchHandler=function(t){return arguments.length?(w=t,z):(w=_,z)},z.setDetailsHandler=function(t){return arguments.length?(M=t,z):(M=x,z)},z},Object.defineProperty(t,"__esModule",{value:!0})});
    </script>
    <script type="text/javascript">
    var flameGraph = d3.flamegraph()
      .width(1023)
      .cellHeight(18)
      .transitionDuration(750)
      .minFrameSize(5)
      .transitionEase(d3.easeCubic)
      .sort(true)
      //Example to sort in reverse order
      //.sort(function(a,b){ return d3.descending(a.name, b.name);})
      .title("")
      .onClick(onClick)
      .differential(false)
      .elided(false)
      .selfValue(false);


    // Example on how to use custom tooltips using d3-tip.
    // var tip = d3.tip()
    //   .direction("s")
    //   .offset([8, 0])
    //   .attr('class', 'd3-flame-graph-tip')
    //   .html(function(d) { return "name: " + d.data.name + ", value: " + d.data.value; });

    // flameGraph.tooltip(tip);

    var details = document.getElementById("details");
    flameGraph.setDetailsElement(details);

    // Example on how to use custom labels
    // var label = function(d) {
    //  return "name: " + d.name + ", value: " + d.value;
    // }
    // flameGraph.label(label);

    // Example of how to set fixed chart height
    // flameGraph.height(540);

  d3.select("#chart")
          .datum($$WHOISYOURDADDY$$)
          .call(flameGraph);
          
    document.getElementById("form").addEventListener("submit", function(event){
      event.preventDefault();
      search();
    });

    function search() {
      var term = document.getElementById("term").value;
      flameGraph.search(term);
    }

    function clear() {
      document.getElementById('term').value = '';
      flameGraph.clear();
    }

    function resetZoom() {
      flameGraph.resetZoom();
    }

    function onClick(d) {
      console.info("Clicked on " + d.data.name);
    }
    </script>
  </body>
</html>

'''


class StackFrame:

    def __init__(self, parent, name, frame_map):
        self._parent = parent
        self._name = name
        self._value = 0
        self._frame_map = frame_map
        if parent:
            self._id = parent.NextId(name)
        else:
            self._id = md5.new(name)
        self._children = {}
        self._frame_map[self.Id] = self

    @property
    def Id(self):
        return self._id.hexdigest()

    def Enter(self, name):
        if name in self._children:
            return self._children[name]
        ret = StackFrame(self, name, self._frame_map)
        self._children[name] = ret
        return ret

    def Leave(self):
        return self._parent

    def NextId(self, name):
        ret = self._id.copy()
        ret.update(name)
        return ret

    def Update(self, amount):
        self._value += amount
        """
        if self._parent:
          self._parent.Update(amount)
        """

    def Print(self):
        value = self._value
        buf = []

        buf.append("{\n")
        buf.append('"name":"%s"' % self._name)
        if self._children:
            buf.append(',\n"children":[')
            sp = ""
            for child in self._children.values():

                v2, b2 = child.Print()
                if b2:
                    buf.append(sp)
                    sp = ","
                    buf.append(b2)
                    value += v2
            buf.append(']')
            if sp == "":  # empty
                buf.pop()
                buf.pop()
        buf.append(',"value":%d}\n' % value)
        if value:
            return value, ''.join(buf)
        return value, None


ctx = {'enter': 0, 'leave': 0}

def formatByteSize(size):
    if size > (1024 * 1024):
        return "%0.2f MB" % (size / 1024.0 / 1024.0)
    elif size > 1024:
        return "%0.2f KB" % (size / 1024.0)
    else:
        return "%d B" % (size,)


def nl2br(txt):
    txt = txt.replace("\n\r", "<br/>")
    txt = txt.replace("\r\n", "<br/>")
    txt = txt.replace("\n", "<br/>")
    txt = txt.replace("\r", "<br/>")
    return txt

class CallStack:

    def __init__(self):
        frame_map = {}
        addr_stat = {}
        self._id = 0
        self._root = StackFrame(None, "_root", frame_map)
        self._cursor = self._root
        self._frame_map = frame_map
        self._addr_stat = addr_stat
        self._layer = 0

    @property
    def CurentId(self):
        return self._cursor.Id

    def Enter(self, name):
        self._cursor = self._cursor.Enter(name)
        self._layer += 1
        pass

    def Leave(self):
        self._cursor = self._cursor.Leave()
        self._layer -= 1
        pass

    def Alloc(self, addr, size):
        stack_id = self.CurentId
        self._addr_stat[addr] = (stack_id, size)
        self._frame_map[stack_id].Update(size)
        # print "alloc %d at %x layer:%d" % (size, addr, self._layer)
        pass

    def Free(self, addr):
        stack_id, size = self._addr_stat.pop(addr, (None, None))
        if stack_id:
            self._frame_map[stack_id].Update(-size)
        # print "free %x" % (addr)
        pass
    
    def Have(self, addr):
        return addr in self._addr_stat
        
    def Reset(self):
        while self._layer > 0:
            self.Leave()

    def FormatReport(self, report):
        total_malloc_size, modules = report['total_malloc_size'], report['modules']

        html = "<div>"

        # Module List
        html += ("<h2>[Native Heap]Module Memory Distribution:</h2>\n")
        html += ("""
         <table class="table table-striped">
             <tr>
                <th>num</th>
                <th>module</th>
                <th>size</th>
                <th>percent</th>
            </tr>
        """)
        count = 1
        for module in modules:
            html += ("<tr>\n")
            html += ("    <td>Top %d</td>\n" % count)
            html += ("    <td>%s</td>\n" % module['so_name'])
            html += ("    <td>%s</td>\n" % formatByteSize(module['size']))
            html += ("    <td>%.2f%%</td>\n" % float(module['size'] / (total_malloc_size * 1.0) * 100) )
            html += ("</tr>\n")
            count += 1
        html += ("</table>\n")
        html += "</div>"

        html += "<div>\n"
        html += "<h2>[Dumpsys] meminfo</h2>\n"
        html += '<pre class="pre-scrollable">\n'
        html += nl2br(report['dumpsys'])
        html += nl2br(report['meminfoN'])
        html += "</pre>\n"
        html += "</div>\n"

        return html

    def Print(self):
        _v, _s = self._root.Print()
        #subhtml = self.FormatReport(report)
        html = TEMPLATE.replace('$$WHOISYOURDADDY$$', _s)
        #html = html.replace("{modules_div}", subhtml)
        return html


def walk(cur, l):
    l.append(cur)
    if cur._value != 0:
        for frame in l[::-1]:
            BOTTOM_UP.Enter(frame._name)
        BOTTOM_UP._cursor.Update(cur._value)
        for frame in l[::-1]:
            BOTTOM_UP.Leave()
    for child in cur._children.values():
        walk(child, l)
    l.pop()


def test():
    CALL_SATCK = CallStack({}, {})
    CALL_SATCK.Enter("layer1")
    CALL_SATCK.Alloc(1, 11)
    CALL_SATCK.Alloc(2, 22)
    CALL_SATCK.Enter("layer2")
    CALL_SATCK.Alloc(3, 33)
    CALL_SATCK.Alloc(4, 44)
    CALL_SATCK.Leave()
    CALL_SATCK.Free(1)
    CALL_SATCK.Free(3)
    CALL_SATCK.Leave()
    CALL_SATCK.Enter("layer1.1")
    CALL_SATCK.Alloc(5, 55)
    CALL_SATCK.Enter("layer2")
    CALL_SATCK.Enter("layer3")
    CALL_SATCK.Alloc(7, 7)
    CALL_SATCK.Enter("layer4")
    CALL_SATCK.Alloc(6, 66)
    CALL_SATCK.Leave()
    CALL_SATCK.Leave()
    CALL_SATCK.Leave()
    CALL_SATCK.Leave()
    CALL_SATCK.Print()
    # for i in CALL_SATCK._root._children.values():
    #  walk(i, [])
    # BOTTOM_UP.Print()


# -----------------------------------------STACK_BUILDER------------------------------------------


import sys, re, os
import subprocess
import cgi

# ndk_root = r"D:\tools\android\android-ndk\android-ndk-r11c-windows-x86_64\android-ndk-r11c"
ndk_root = r"C:\ndk\android-ndk-r11c"
# ndk_root = r"C:\Users\Admin\AppData\Local\Android\sdk\ndk-bundle"
addr2line_exe = ndk_root + r"\toolchains\arm-linux-androideabi-4.9\prebuilt\windows-x86_64\bin\arm-linux-androideabi-addr2line.exe"

ptn_pc = re.compile(r'(?P<bt>\d+)\s+#(?P<f>\d+) (?P<pc>[0-9a-f]+) (?P<dso>.+) \+(?P<o>[0-9a-f]+)')
ptn_pcref = re.compile(r'(?P<bt>\d+)\s+#(?P<f>\d+) >(?P<r>\d+)')

STEP = 1000


def parse_addr(pcmap):
    somap = {}
    retmap = {}
    retlst = [None] * len(pcmap)
    for idx, (soname, offset) in enumerate(pcmap):
        if soname.startswith('/data/'):
            sympath = 'symbols\\datalib\\' + os.path.basename(soname)
        elif soname.startswith('/system/lib'):
            sympath = 'symbols\\syslib\\' + os.path.basename(soname)
        else:
            continue
        if not os.path.isfile(sympath):
            continue
        if sympath not in somap:
            somap[sympath] = []
        l = somap[sympath]
        l.append((offset, idx))
    # print somap
    for symname in somap:
        l = somap[symname]
        for i in range(0, len(l), STEP):
            offs = l[i: i + STEP]
            args = [j[0] for j in offs]
            out = subprocess.check_output([addr2line_exe, "-Cf", "-e", symname] + args).split('\n')
            # print symname, len(out), len(args)
            for j in range(len(args)):
                retlst[offs[j][1]] = out[j * 2].strip()
    for i in range(len(retlst)):
        if retlst[i] == None:
            retlst[i] = os.path.basename(pcmap[i][0])
    return retlst


def load_stack_txt(pid):
    pcmap = []
    btmap = []
    with open("MallocMon\\stack.%d.txt" % pid, 'rb') as fp:
        frames = []
        cur = 1
        for line in fp:
            if cur % 10000 == 0: print ".",
            #if cur > 10000: break  # FIXME
            # print line
            matched = ptn_pcref.match(line)
            if matched:
                gd = matched.groupdict()
                bt, f, r = int(gd['bt']), int(gd['f']), int(gd['r'])
                if bt != cur:
                    btmap.append(frames)
                    assert len(btmap) == cur
                    cur = bt
                    frames = []
                frames.append(r)
                # print frames, f
                assert len(frames) == f
                continue
            matched = ptn_pc.match(line)
            if matched:
                gd = matched.groupdict()
                bt, f, pc, dso, o = int(gd['bt']), int(gd['f']), gd['pc'], gd['dso'], gd['o']
                pcmap.append((dso, o))
                r = len(pcmap)
                if bt != cur:
                    btmap.append(frames)
                    assert len(btmap) == cur
                    cur = bt
                    frames = []
                frames.append(r)
                # print frames, f
                assert len(frames) == f
    print len(pcmap), len(btmap)
    print "start parse_addr"
    parsed_pcmap = parse_addr(pcmap)
    print "parse_addr done"
    return pcmap, parsed_pcmap, btmap


ptn_alloc = re.compile(r'x (?P<bt>\d+) sz (?P<sz>\d+) \+(?P<p>\d+) \-(?P<n>\d+)')

#################################################################

self_modules = [
    "libAkSoundEngine.so",
    "libanw.10.so",
    "libanw.13.so",
    "libanw.14.so",
    "libanw.18.so",
    "libanw.21.so",
    "libBlueDoveMediaRender.so",
    "libBugly-msdk.so",
    "libcubehawk.so",
    "libDraw.so",
    "libGCloudVoice.so",
    "libgnustl_shared.so",
    "libil2cpp.so",
    "libiomx.10.so",
    "libiomx.13.so",
    "libiomx.14.so",
    "libjniloader.so",
    "libJX3MWorld.so",
    "libmain.so",
    "libMSDK.so",
    "libMsdkAdapter.so",
    "libMSDKSystem.so",
    "libpandora.so",
    "libslua.so",
    "libsqlite3.so",
    "libsubstrate.so",
    "libtersafe.so",
    "libtpnsSecurity.so",
    "libu3dperf.so",
    "libunity.so",
    "libUniversalMediaPlayer.so",
    "libvlcjni.so",
    "libxguardian.so"
]


#################################################################

def main3(pid, idx):
    origin_pc_map, pcmap, btmap = load_stack_txt(pid)

    btsomap = []  # 和btmap一样, index还是pc的index, 但是保存的是所属module的soname,
    assert len(origin_pc_map) == len(pcmap)
    pcmaplen = len(origin_pc_map)

    for bt in btmap:
        module_name = None
        last_so_name = None
        for pc_index in bt:
            frame = origin_pc_map[pc_index - 1]
            so_name = frame[0]
            pc = frame[1]
            last_so_name = so_name
            so_file_name = os.path.basename(so_name)
            if module_name is None and so_file_name in self_modules:
                module_name = so_name
        if module_name is None:
            module_name = last_so_name
        btsomap.append(module_name)

    modules = {}

    cs = CallStack({}, {})
    total_malloc_size = 0
    total_malloc_count = 0
    total_free_count = 0
    with open('MallocMon\\heap.%d.%d.txt' % (pid, idx), 'rb') as fp:
        lineCount = 0
        for line in fp:
            if lineCount % 10000 == 0: print ".",
            lineCount +=1
            matched = ptn_alloc.match(line)
            if not matched: continue
            gd = matched.groupdict()
            bt, sz, p, n = int(gd['bt']), int(gd['sz']), gd['p'], gd['n']
            bt -= 1
            if bt >= len(btmap):
                continue
            for stackid in btmap[bt][::-1]:
                cs.Enter(pcmap[stackid - 1] if stackid < len(pcmap) else "NULL")
                # print pcmap[stackid - 1] if stackid < len(pcmap) else "NULL"
            cs._cursor.Update(sz)
            for stackid in btmap[bt]:
                cs.Leave()

            module_name = btsomap[bt]
            if module_name not in modules:
                modules[module_name] = {}
                modules[module_name]['so_name'] = module_name
                modules[module_name]['size'] = 0
                modules[module_name]['malloc_count'] = 0
                modules[module_name]['free_count'] = 0
            modules[module_name]['size'] += sz
            modules[module_name]['malloc_count'] += int(p)
            modules[module_name]['free_count'] += int(n)
            total_malloc_size += sz
            total_malloc_count += int(p)
            total_free_count += int(n)


    dumpsys = open('MallocMon\\dumpsys.%d.%d.txt' % (pid, idx), 'rb').read()
    meminfo0 = open('MallocMon\\meminfo.%d.%d.txt' % (pid, 0), 'rb').read()
    meminfoN = open('MallocMon\\meminfo.%d.%d.txt' % (pid, idx), 'rb').read()

    #print modules
    modules = modules.values()
    modules.sort(key=lambda module: module['size'], reverse=True)

    report = {}
    report['total_malloc_size'] = total_malloc_size
    report['total_malloc_count'] = total_malloc_count
    report['total_free_count'] = total_free_count
    report['dumpsys'] = dumpsys
    report['meminfo0'] = meminfo0
    report['meminfoN'] = meminfoN
    report['modules'] = modules

    with open("framegraph.%d.%d.html" % (pid, idx), "wb") as fp:
        fp.write(cs.Print(report))

bt_ptn = re.compile(r'(?P<bt>0x[a-fA-F0-9]+) \[LUASTACK\]=(?P<lua>.*)')
#[C](-1):0xcc01f800:cs_func
lua_fun_ptr = re.compile(r'.*:(?P<ptr>0x[a-fA-F0-9]+):.*')
csharp_fun_ptr = re.compile(r'.*\((?P<ptr>0x[a-fA-F0-9]+)\)$')

def load_bt_map(pid):
    btmap = {}
    line_cnt = 0
    cfunmap = {}
    with open("stack.%s.txt" % pid, "rb") as fp:
        for line in fp:
            line_cnt += 1
            #if line_cnt > 10000: break # FIXME
            matched = bt_ptn.match(line.strip())
            if not matched:
                print "skip line not matched:", line.strip()
                continue
            gd = matched.groupdict()
            gd['lua'] = gd['lua'].strip().replace('"', "'").replace('\\', '/').replace('\t',' ')
            bt, lua = gd['bt'], gd['lua']

                
            _bt =  filter(None, lua.split("|"))
            
            real_bt = []
            for i in range(0, len(_bt)):
                cfun = _bt[i].split()
                funname = _bt[i]
                if len(cfun) == 2 and cfun[0] == 'CFUN':
                    if cfun[1] in cfunmap:
                        funname = cfunmap[ cfun[1] ]
                    else:
                        out = subprocess.check_output(['addr2line', "-Cf", "-e", '/data/app/server/bin/Server', cfun[1]]).split('\n')
                        outname = ''
                        if len(out) > 0:
                            outname = out[0]
                            
                        cfunmap[ cfun[1] ] = outname
                        funname = outname
                         
                #print funname
                real_bt.append(funname)        
            btmap[bt] = real_bt[::-1]
            continue
            #if bt in btmap:
            #    print "skip duplicated bt:", bt
            #    continue
            
            allstack = []
                
            luastack = filter(None, lua.split("|"))
            csharpstack = filter(None, cs.split("|"))
            
            csindex = 0
            for i in range(len(luastack)):
                matched = lua_fun_ptr.match(luastack[i].strip())
                
                if not matched:
                    allstack.append(luastack[i])
                    continue
                    

                gd = matched.groupdict()
                if gd['ptr'] == '0x0':
                    allstack.append(luastack[i])
                    continue
                    
                #print gd['ptr']
                
                for j in range(csindex, len(csharpstack)):
                    matched1 = csharp_fun_ptr.match(csharpstack[j])
                    if matched1:
                        gd1 = matched1.groupdict()
                        if gd1['ptr'] == gd['ptr']:
                            allstack = allstack + csharpstack[csindex:j+1]
                            allstack.append(luastack[i])
                            csindex = j+1
                                    
            
            allstack = allstack + csharpstack[csindex:]
            
            """
            cs2lua_list = []
            _tmp = []                
            for lf in luastack:
                matched = lua_fun_ptr.match(lf.strip())
                if matched:
                    gd = matched.groupdict()
                    cs2lua_list.append((gd['ptr'], _tmp))
                    _tmp = []
                    continue
                else:
                    _tmp.append(lf)
            if len(cs2lua_list) >1 : print cs2lua_list
            """
            _bt = allstack
            btmap[bt] = _bt[::-1]
            
    return btmap


mem_ptn = re.compile(r'size=(?P<s>[0-9]+) StackPtr=(?P<bt>0x[0-9a-fA-F]+).*')

def main(pid):
    btmap = load_bt_map(pid)
    # print btmap
    fg = CallStack()
    target_ls = None
    line_cnt = 0
    with open("lualog.%s.txt" % pid, "rb") as fp:
        for line in fp:
            line_cnt += 1
            #if line_cnt > 100000: break # FIXME
            line = line.strip()
            matched = mem_ptn.match(line)
            if matched:
                gd = matched.groupdict()
                s, bt = gd['s'], gd['bt']
                #print s
                #print bt
                fg.Reset()
                if bt not in btmap:
                    print "bt %s not in btmap" % bt
                    continue
                
                if len(btmap[bt]) <= 1:
                    print 'ERROR'
                    continue
                for fm in btmap[bt]:
                    fg.Enter(fm)
                # "enter layer: %d" % fg._layer
                fg.Alloc(1, int(s))
                continue
                
    with open("luamem.%s.html" % (pid, ), "wb") as fp:
        fp.write(fg.Print())
        
if __name__ == "__main__":
    if len(sys.argv) >= 2:
        main(sys.argv[1])
    else:
        load_stack_txt(999)

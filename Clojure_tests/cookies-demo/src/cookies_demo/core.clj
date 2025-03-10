(ns cookies-demo.core
  (:require [ring.adapter.jetty]
            [ring.middleware.cookies]
            [compojure.core])
  (:use [clojure.string]))

;;
;; Setting cookies
;;

;; Using a 'Set-Header' as described in
;; https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Set-Cookie
(defn set-cookie-raw [request]
  {:status 200
   :headers {"Content-Type" "text/html"
             "Set-Cookie" "session=123456; Path=/; Max-Age=84600"}
   :body "<p>I set one cookie named <tt>session</tt></p>"})

;; Using ':cookies' in the response map (put there by the middleware) as
;; described in https://github.com/ring-clojure/ring/wiki/Cookies
;; The middleware turns this into multiple 'Set-Header' response headers like
;; the one in set-cookie-raw.  For multiple cookies, the above doesn't work
;; because map keys must be unique.  Also note: It seems that when your response
;; map has a :cookies key, it cannot have a 'Set-Cookie' in the headers.
(defn set-cookies-middleware [request]
  {:status 200
   :headers {"Content-Type" "text/html"}
   :cookies {"middleware-session" {:value "987654321" :path "/" :max-age 86400}
             "middleware-other" {:value "123456789abcdef" :path "/show-cookies" :max-age 3600}}
   :body "<p>I set two cookies: one named <tt>middleware-session</tt> and one named <tt>middleware-other</tt></p>"})

;;
;; Accessing the values of cookies
;;

;; Using 'Cookies' request header as described in
;; https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Cookie
;; Note: The received cookies only are '<name>=<value>; <name>=<Value>...' and
;; the attributes only control which cookies the browser sends.
(defn cookies-html-table-raw [cookie]
  (let [cookies (map #(clojure.string/split % #"=")
                     (clojure.string/split cookie #"; *"))]
    (str "<table><tr><th>Name</th><th>Value</th></tr>"
         (join "\n" (for [[name value] cookies]
                      (format "<tr><td>%s</td><td style=\"max-width:500px\">%s</td></tr>"
                              name value)))
         "</table>")))

;; Get the value of the 'Cookies' header and pass it along to
;; cookies-html-table-raw
(defn show-cookies-raw [request]
  (let [cookie (get-in request [:headers "cookie"])]
    {:status 200
     :headers {"Content-Type" "text/html"}
     :body (str "<H1>Cookies sent by browser via 'Cookie' header</H1>"
                (cookies-html-table-raw (:cookies request)))}))

;; Using ':cookies' in the request map (put there by the middleware) as
;; described in https://github.com/ring-clojure/ring/wiki/Cookies
(defn cookies-html-table-middleware [cookies]
  (str "<table><tr><th>Name</th><th>Value</th></tr>"
       (join "\n" (for [[name value] cookies]
                    (format "<tr><td>%s</td><td style=\"max-width:500px\">%s</td></tr>"
                            name (:value value))))
       "</table>"))

;; Get the value of the :cookies key in the request map and pass it along to
;; cookies-html-table-middleware
(defn show-cookies-middleware [request]
    {:status 200
     :headers {"Content-Type" "text/html"}
     :body (str "<H1>Cookies sent by browser via 'Cookie' header</H1>"
                (cookies-html-table-middleware (:cookies request)))})

(compojure.core/defroutes my-routes
  (compojure.core/GET "/set-cookie-raw" request
                      (ring.middleware.cookies/wrap-cookies set-cookie-raw))
  (compojure.core/GET "/set-cookies-middleware" request
                      (ring.middleware.cookies/wrap-cookies set-cookies-middleware))
  (compojure.core/GET "/show-cookies-raw" request
                      (ring.middleware.cookies/wrap-cookies show-cookies-raw))
  (compojure.core/GET "/show-cookies-middleware" request
                      (ring.middleware.cookies/wrap-cookies show-cookies-middleware))
  (compojure.core/ANY "*" request {:status 404
                                   :headers {"Content-Type" "text/html"}
                                   :body (str "<H1>Not Found</H1>"
                                              "<p>Routes are /set-cookie-raw,"
                                              "/set-cookies-middleware, /show-cookies</p>")}))

(defn -main
  "Main function"
  [& args]
  (ring.adapter.jetty/run-jetty my-routes {:port 8989}))

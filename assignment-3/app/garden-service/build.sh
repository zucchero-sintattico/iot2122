cp -R lib http-component
cp -R ../garden-dashboard http-component
cp -R lib logic-component
cp -R lib mqtt-component
if [ $# -eq 0 ]
  then
    docker compose up -d --build
  else
    for service in "$@"
    do
        docker compose up -d --build --no-deps $service
    done
fi

rm -rf http-component/lib/
rm -rf http-component/garden-dashboard/
rm -rf logic-component/lib/
rm -rf mqtt-component/lib/